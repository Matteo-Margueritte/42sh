/*
** right_redirection.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src/execution
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Thu Oct 20 23:58:53 2016 Matteo
** Last update Sun Oct 23 14:37:40 2016 Matteo
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "parser.h"
#include "shell.h"

static int	open_or_create_file(char *name, int type)
{
  int		fd;

  fd = -1;
  if (type == D_RIGHT)
    fd = open(name, O_WRONLY | O_CREAT | O_APPEND, FILE_RIGHTS);
  else if (type == RIGHT)
    fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, FILE_RIGHTS);
  if (fd == -1)
    fprintf(stderr, "Error open\n");
  return (fd);
}

int		right_redirection(t_node *tree, t_shell *st_shell)
{
  int		fd;

  if (tree->right == NULL || tree->left == NULL)
    return (FAILURE);
  if ((fd = open_or_create_file(tree->right->args[0], tree->type)) == -1)
    return (FAILURE);
  set_fd_out(tree->left, fd);
  return (execute_it(tree->left, st_shell));
}
