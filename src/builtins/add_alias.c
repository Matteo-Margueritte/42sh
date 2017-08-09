/*
** add_alias.c for alias in /home/nagamo_s/rendu/PSU_2015_42sh/src/builtins
**
** Made by stephane
** Login   <nagamo_s@epitech.net>
**
** Started on  Mon Oct 24 18:44:48 2016 stephane
** Last update Mon Oct 24 22:44:55 2016 Matteo
*/

#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "shell.h"

char		**add_cmd(char **cmd)
{
  char		**tab;
  int		i;
  int		j;
  int		k;

  i = 0;
  while (cmd[i] != NULL)
    i = i + 1;
  if (!(tab = malloc(sizeof(char *) * (i))))
    return (NULL);
  i = 1;
  k = 0;
  while (cmd[++i] != NULL)
    {
      j = -1;
      if (!(tab[k] = malloc(sizeof(char) * (strlen(cmd[i]) + 1))))
	return (NULL);
      while (cmd[i][++j] != '\0')
	tab[k][j] = cmd[i][j];
      tab[k++][j] = '\0';
      tab[k] = NULL;
    }
  return (tab);
}

static int	check_alias(char **tab, t_alias *list_alias)
{
  while (strcmp(tab[1], list_alias->alias) != 0 && list_alias->next != NULL)
    list_alias = list_alias->next;
  if (strcmp(tab[1], list_alias->alias) == 0)
    {
      free_tab(list_alias->cmd);
      if (!(list_alias->cmd = add_cmd(tab)))
	return (0);
    }
  return (1);
}

t_alias		*add_to_alias(char **tab, t_alias *list_alias)
{
  t_alias	*new_alias;

  if (!(check_alias(tab, list_alias)))
    return (list_alias);
  if (!(new_alias = malloc(sizeof(t_alias))))
    return (NULL);
  new_alias->loop = 0;
  new_alias->prev = NULL;
  new_alias->next = list_alias;
  list_alias->prev = new_alias;
  if (!(new_alias->alias = strdup(tab[1])))
    return (NULL);
  if (!(new_alias->cmd = add_cmd(tab)))
    return (NULL);
  return (new_alias);
}
