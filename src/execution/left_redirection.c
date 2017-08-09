/*
** left_redirection.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src/execution
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Thu Oct 20 23:58:16 2016 Matteo
** Last update Sat Oct 22 00:00:31 2016 Matteo
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "parser.h"
#include "shell.h"

static int	open_file(char *name)
{
  int		fd;

  if (access(name, F_OK) == -1 || access(name, R_OK) == -1)
    {
      if (access(name, F_OK) == -1)
	fprintf(stderr, "%s: no such file or directory.\n", name);
      else
	fprintf(stderr, "%s: Permission denied.\n", name);
      return (-1);
    }
  fd = open(name, O_RDONLY);
  if (fd == -1)
    fprintf(stderr, "%s: Failed to open.\n", name);
  return (fd);
}

int		spe_left(t_node *tree)
{
  int		fd;
  char		**args;

  if (tree->right != NULL)
    args = tree->right->args;
  else
    args = NULL;
  if (!args || !args[0] || (fd = open_file(args[0])) == -1)
    return (FAILURE);
  set_fd_in(tree->left, fd);
  return (SUCCESS);
}

int		left_redirection(t_node *tree, t_shell *shell)
{
  int		fd;
  char		**args;

  args = tree->right->args;
  if (!args || !args[0] || (fd = open_file(args[0])) == -1)
    return (FAILURE);
  set_fd_in(tree->left, fd);
  return (execute_it(tree->left, shell));
}
