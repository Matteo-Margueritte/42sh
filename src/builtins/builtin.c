/*
** check_builtin.c for 42sh in /home/gayrau_a/rendu_tek1/S2/PSU/PSU_2015_42sh/src/builtins
**
** Made by gayrau_a
** Login   <gayrau_a@epitech.net>
**
** Started on  Thu Oct 20 15:52:42 2016 gayrau_a
** Last update Fri Oct 21 20:42:57 2016 Matteo
*/

#include <stdlib.h>
#include <string.h>
#include "builtin.h"

int			exec_builtin(char **tab, t_shell *shell)
{
  int			i;

  i = 0;
  while (strcmp(g_builtin[i].arg, tab[0]) != 0)
    i = i + 1;
  return (g_builtin[i].fct(tab, shell));
}

int			check_builtin(char *builtin)
{
  int			i;

  i = 0;
  while (g_builtin[i].arg != NULL)
    {
      if (strcmp(g_builtin[i].arg, builtin) == 0)
	return (EXIT_SUCCESS);
      i = i + 1;
    }
  return (EXIT_FAILURE);
}
