/*
** my_cd.c for cd in /home/vidal_s/rendu/PSU/S2/PSU_2015_42sh/src
**
** Made by sebastien vidal
** Login   <vidal_s@epitech.net>
**
** Started on  Tue Oct 18 12:07:04 2016 sebastien vidal
** Last update Mon Oct 24 19:22:09 2016 sebastien vidal
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "builtin.h"
#include "utils.h"

static int	cd_home(t_shell *shell)
{
  char		*home;

  if (!(home = get_env_line("HOME")))
    return (EXIT_FAILURE);
  free(shell->oldpwd);
  if (!(shell->oldpwd = strdup(shell->pwd)))
    return (EXIT_FAILURE);
  if (chdir(home) == -1)
    {
      fprintf(stderr, "Home path is corrupted\n");
      return (EXIT_FAILURE);
    }
  free(home);
  free(shell->pwd);
  if (!(shell->pwd = getcwd(NULL, 0)))
    return (EXIT_FAILURE);
  if (change_pwd(shell) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

static int	check_arg_cd(char **arg)
{
  int		i;

  i = 0;
  while (arg[i] != NULL)
    i = i + 1;
  if (i != 2)
    {
      fprintf(stderr, "Usage : cd <path>\n");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

static int	simple_cd(char **arg, t_shell *shell)
{
  free(shell->oldpwd);
  if (!(shell->oldpwd = strdup(shell->pwd)))
    return (EXIT_FAILURE);
  if (chdir(arg[1]) == -1)
    {
      fprintf(stderr, "%s: Not a directory.\n", arg[1]);
      return (EXIT_FAILURE);
    }
  free(shell->pwd);
  if (!(shell->pwd = getcwd(NULL, 0)))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

static int	check_cd(char**arg, t_shell *shell)
{
  if (strcmp("-", arg[1]) == 0)
    {
      if (my_cd_dash(shell) == EXIT_FAILURE)
	return (EXIT_FAILURE);
      return (EXIT_SUCCESS);
    }
  if (access(arg[1], F_OK) == -1)
    {
      fprintf(stderr, "%s: Aucun fichier ou dossier de ce type.\n", arg[1]);
      return (EXIT_FAILURE);
    }
  else if (access(arg[1], R_OK) == -1)
    {
      fprintf(stderr, "%s: Permission non accordée.\n", arg[1]);
      return (EXIT_FAILURE);
    }
  if (simple_cd(arg, shell) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int		my_cd(char **arg, t_shell *shell)
{
  if (arg[1] == NULL)
    return (cd_home(shell));
  if (check_arg_cd(arg) == EXIT_FAILURE ||
      check_cd(arg, shell) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
