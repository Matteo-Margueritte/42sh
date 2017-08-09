/*
** my_cd_dash.c for 42sh in /home/vidal_s/rendu/PSU/S2/PSU_2015_42sh/src/builtins
**
** Made by sebastien vidal
** Login   <vidal_s@epitech.net>
**
** Started on  Sat Oct 22 20:55:38 2016 sebastien vidal
** Last update Mon Oct 24 19:18:54 2016 sebastien vidal
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "builtin.h"
#include "utils.h"

int		change_pwd(t_shell *shell)
{
  t_env		*tmp;

  tmp = g_env;
  while (tmp != NULL)
    {
      if (strcmp("PWD", tmp->env_line) == 0)
	{
	  if (tmp->env_line != NULL)
	    {
	      free(tmp->env_line);
	      if (!(tmp->env_line = malloc(sizeof(char) *
					   (strlen(shell->pwd) + 4)))
		  || (tmp->env_line = strcpy(tmp->env_line, "PWD")) == NULL ||
		  (tmp->env_line = strcat(tmp->env_line, shell->pwd)) == NULL)
		return (EXIT_FAILURE);
	    }
	}
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}

int		my_cd_dash(t_shell *shell)
{
  char		*str;

  str = NULL;
  if (chdir(shell->oldpwd) == -1)
    {
      fprintf(stderr, "OLDPWD path is corrupted.\n");
      return (EXIT_FAILURE);
    }
  str = shell->pwd;
  shell->pwd = shell->oldpwd;
  shell->oldpwd = str;
  if (change_pwd(shell) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
