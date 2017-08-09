/*
** my_exit.c for 42sh in /home/vidal_s/rendu/PSU/S2/PSU_2015_42sh/src
**
** Made by sebastien vidal
** Login   <vidal_s@epitech.net>
**
** Started on  Tue Oct 18 17:02:34 2016 sebastien vidal
** Last update Sat Oct 22 19:36:28 2016 Matteo
*/

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

int		my_exit(char **tab, t_shell *shell)
{
  int		status;

  if (tab == NULL)
    {
      shell->exit_status = FAILURE;
      return (FAILURE);
    }
  else if (tab[1] != NULL)
    {
      status = my_getnbr(tab[1]);
      if (tab[2] != NULL || status == -1)
	{
	  fprintf(stderr, "exit: Expression Syntax.\n");
	  return (FAILURE);
	}
      shell->exit_status = status;
      return (SUCCESS);
    }
  shell->exit_status = SUCCESS;
  return (SUCCESS);
}
