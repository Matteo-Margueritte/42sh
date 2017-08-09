/*
** alias.c for 42sh in /home/nagamo_s/rendu
**
** Made by stephane
** Login   <nagamo_s@epitech.net>
**
** Started on  Wed Oct 19 14:00:43 2016 stephane
** Last update Mon Oct 24 22:44:36 2016 Matteo
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

static t_alias		*init_alias(char **tab)
{
  t_alias		*list_alias;

  if (!(list_alias = malloc(sizeof(t_alias))))
    return (NULL);
  list_alias->prev = NULL;
  list_alias->loop = 0;
  list_alias->next = NULL;
  if (!(list_alias->alias = strdup(tab[1])))
    return (NULL);
  if (!(list_alias->cmd = add_cmd(tab)))
    return (NULL);
  return (list_alias);
}

int		my_alias(char **tab, t_shell *shell)
{
  int		i;

  if ((i = check_arg(tab)) != 0)
    {
      if (i == 2)
	return (0);
      else
	return (1);
    }
  if (tab[1] == NULL || tab[2] == NULL)
    {
      print_alias(shell, tab);
      return (0);
   }
  if (shell->list_alias == NULL)
    {
      if (!(shell->list_alias = init_alias(tab)))
	return (1);
    }
  else
    if (!(shell->list_alias = add_to_alias(tab, shell->list_alias)))
      return (1);
  shell->list_alias = check_loop(shell->list_alias);
  shell->list_alias = check_list(shell->list_alias);
  return (0);
}
