/*
** check_other_symbols.c for 42sh in /home/matteo/rendu/test/parseur
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 11:57:46 2016 Matteo
** Last update Sat Oct 22 15:15:53 2016 Matteo
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "parser.h"

int		is_redir_no_pipe(char *str)
{
  if (is_left_redir(str) == SUCCESS || is_right_redir(str) == SUCCESS)
    return (SUCCESS);
  return (FAILURE);
}

int		is_redir(char *str)
{
  if (is_left_redir(str) == SUCCESS || is_right_redir(str) == SUCCESS
      || is_pipe(str) == SUCCESS)
    return (SUCCESS);
  return (FAILURE);
}

int		is_sep(char *str)
{
  if (is_and_or_or_bin(str) == SUCCESS)
    return (SUCCESS);
  return (FAILURE);
}

int		is_redir_or_sep(char *s)
{
  if (is_left_redir(s) == SUCCESS || is_right_redir(s) == SUCCESS
      || is_sep(s) == SUCCESS || is_pipe(s) == SUCCESS)
    return (SUCCESS);
  return (FAILURE);
}
