/*
** check_symbols.c for 42sh in /home/matteo/rendu/test/parseur
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 11:58:05 2016 Matteo
** Last update Sat Oct 22 15:00:51 2016 Matteo
*/

#include <string.h>
#include "parser.h"

int		is_left_redir(char *str)
{
  if (str && (!strcmp(str, R_LEFT) || !strcmp(str, DR_LEFT)))
    return (SUCCESS);
  return (FAILURE);
}

int		is_right_redir(char *str)
{
  if (str && (!strcmp(str, R_RIGHT) || !strcmp(str, DR_RIGHT)))
    return (SUCCESS);
  return (FAILURE);
}

int		is_pipe(char *str)
{
  if (str && !strcmp(str, PIPE))
    return (SUCCESS);
  return (FAILURE);
}

int		is_and_or_or_bin(char *str)
{
  if (str && (!strcmp(str, AND) || !strcmp(str, OR)))
    return (SUCCESS);
  return (FAILURE);
}
