/*
** echo.c for 42sh in /home/gayrau_a/rendu_tek1/S2/PSU/PSU_2015_42sh/src/builtins
**
** Made by gayrau_a
** Login   <gayrau_a@epitech.net>
**
** Started on  Thu Oct 20 15:49:22 2016 gayrau_a
** Last update Sat Oct 22 15:15:08 2016 Matteo
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "builtin.h"
#include "utils.h"

int		echo_arg(char **tab)
{
  int		i;

  i = 1;
  while (tab[i])
    {
      if (strcmp(NEWLINE, tab[i]) == 0)
	return (1);
      i = i + 1;
    }
  return (0);
}

char		*cut_dollar(char *arg)
{
  char		*dest;
  int		i;
  int		u;

  i = 1;
  u = 0;
  if ((dest = malloc(sizeof(char) * strlen(arg))) == NULL)
    return (NULL);
  while (arg[i])
    {
      dest[u] = arg[i];
      u = u + 1;
      i = i + 1;
    }
  dest[u] = '\0';
  return (dest);
}

int		display_env_var(char *arg)
{
  char		*str;

  if ((arg = cut_dollar(arg)) == NULL ||
      ((str = get_env_line(arg)) == NULL))
    return (FAILURE);
  write(1, str, strlen(str));
  free(str);
  return (SUCCESS);
}

int		my_echo(char **tab, t_shell *shell)
{
  int		i;

  i = 1;
  (void)shell;
  while (tab[i])
    {
      if (tab[i][0] == ENV_VAR && tab[i][1] == RET)
	printf("%d", shell->ret);
      else if (tab[i][0] == ENV_VAR)
	{
	  if ((display_env_var(tab[i])) == FAILURE)
	    return (FAILURE);
	}
      else if (strcmp(NEWLINE, tab[i]) != 0)
	write(1, tab[i], strlen(tab[i]));
      i = i + 1;
    }
  if (echo_arg(tab) == 0)
    printf("\n");
  return (SUCCESS);
}
