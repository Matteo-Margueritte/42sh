/*
** initialisation.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 14:21:45 2016 Matteo
** Last update Mon Oct 24 21:36:40 2016 Matteo
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

int		initialisation(t_shell *shell, char **env)
{
  if (!(shell->pwd = getcwd(NULL, 0)) ||
      !(shell->oldpwd = getcwd(NULL, 0)) ||
      (g_env = create_env(env)) == NULL)
    return (FAILURE);
  shell->list_alias = NULL;
  shell->exit_status = -1;
  shell->ret = 0;
  return (SUCCESS);
}
