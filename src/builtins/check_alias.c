/*
** check_aliias.c for alias in /home/nagamo_s/rendu/PSU_2015_42sh/src/builtins
**
** Made by stephane
** Login   <nagamo_s@epitech.net>
**
** Started on  Mon Oct 24 18:54:36 2016 stephane
** Last update Mon Oct 24 19:11:18 2016 stephane
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

t_alias		*check_list(t_alias *list_alias)
{
  t_alias	*tmp;

  while (list_alias->prev != NULL)
    list_alias = list_alias->prev;
  tmp = list_alias;
  if (list_alias->next != NULL)
    {
      list_alias = list_alias->next;
      if (strcmp(list_alias->alias, tmp->alias) == 0)
	list_alias->prev = NULL;
    }
  while (list_alias->prev != NULL)
    list_alias = list_alias->prev;
  return (list_alias);
}

static void	check_list_loop(t_alias *alias, t_alias *tmp)
{
  int		i;
  int		j;

  i = 0;
  while (alias->cmd[i] != NULL)
    {
      if (strcmp(tmp->alias, alias->cmd[i]) == 0 &&
	  strcmp(alias->alias, alias->cmd[i]) != 0)
	{
	  j = 0;
	  while (tmp->cmd[j] != NULL)
	    {
	      if (strcmp(tmp->cmd[j], alias->alias) == 0)
		alias->loop = 1;
	      j = j + 1;
	    }
	}
      i = i + 1;
    }
}

t_alias		*check_loop(t_alias *alias)
{
  t_alias	*tmp;

  tmp = alias;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp->next != NULL)
    {
      check_list_loop(alias, tmp);
      tmp = tmp->next;
    }
  check_list_loop(alias, tmp);
  return (alias);
}

int	check_arg(char **tab)
{
  int	i;

  i = 0;
  while (tab[i] != NULL)
    i = i + 1;
  if (i < 2)
    return (0);
  if (strcmp(tab[0], "alias") == 0
      && strcmp(tab[1], "alias") == 0)
    {
      if (i == 2)
	return (2);
      if (strcmp(tab[2], "alias") == 0)
	printf("alias: Too dangerous to alias that.\n");
      return (1);
    }
  return (0);
}
