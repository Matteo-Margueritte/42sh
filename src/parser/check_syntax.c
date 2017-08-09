/*
** check_syntax.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src/parser
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Mon Oct 24 23:13:26 2016 Matteo
** Last update Mon Oct 24 21:56:41 2016 Matteo
*/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "parser.h"

static int	check_cmd(char **command)
{
  int		i;

  i = -1;
  while (command[++i])
    if (is_redir_or_sep(command[i]) == SUCCESS)
      {
	if (command[i + 1] == NULL)
	  {
	    fprintf(stderr, "Invalid null command.\n");
	    return (FAILURE);
	  }
	if (is_redir_or_sep(command[i + 1]) == SUCCESS)
	  {
	    fprintf(stderr, "Invalid null command.\n");
	    return (FAILURE);
	  }
      }
  return (SUCCESS);
}

int		check_syntax(char *command)
{
  char		**command_tab;

  if ((command_tab = my_str_to_wordtab(command, ' ')) == NULL)
    return (FAILURE);
  if (command_tab[1] == NULL && is_pipe(command_tab[0]) == SUCCESS)
    {
      fprintf(stderr, "Invalid null command.\n");
      free_tab(command_tab);
      return (FAILURE);
    }
  if (check_cmd(command_tab) == FAILURE)
    {
      free_tab(command_tab);
      return (FAILURE);
    }
  free_tab(command_tab);
  return (SUCCESS);
}
