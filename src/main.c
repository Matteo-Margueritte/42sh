/*
** main.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Tue Oct 11 14:35:35 2016 Matteo
** Last update Mon Oct 24 22:46:24 2016 Matteo
*/

#include <stdlib.h>
#include <signal.h>
#include "utils.h"

int		main(int ac, char *av[], char *env[])
{
  t_shell	shell;
  int		status;

  (void)ac;
  (void)av;
  signal(SIGINT, print_prompt);
  if (initialisation(&shell, env) == FAILURE ||
      read_history(&shell) == FAILURE)
    return (EXIT_FAILURE);
  status = prompt(&shell);
  if (write_history(&shell) == FAILURE)
    return (EXIT_FAILURE);
  free_env(g_env);
  free_alias(shell.list_alias);
  free(shell.pwd);
  free(shell.oldpwd);
  return (status);
}
