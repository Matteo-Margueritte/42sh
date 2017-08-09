/*
** executions.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src/execution
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 14:33:16 2016 Matteo
** Last update Mon Oct 24 21:34:54 2016 Matteo
*/

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include "parser.h"

int		execute_it(t_node *tree, t_shell *shell)
{
  int		status;

  status = FAILURE;
  if (tree->type == T_OR &&
      (status = execute_it(tree->left, shell)) == FAILURE)
    return (execute_it(tree->right, shell));
  if (tree->type == T_AND && execute_it(tree->left, shell) == SUCCESS)
    return (execute_it(tree->right, shell));
  else if (tree->type == T_PIPE)
    return (prepare_pipes(tree, shell));
  else if (tree->type == CMD)
    return (simple_exec(tree, shell));
  else if (tree->type == RIGHT || tree->type == D_RIGHT)
    return (right_redirection(tree, shell));
  else if (tree->type == LEFT || tree->type == D_LEFT)
    return (left_redirection(tree, shell));
  return (status);
}

int		main_execution(t_shell *shell)
{
  int		i;
  int		status;

  i = 0;
  status = 0;
  while (shell->trees[i] != NULL)
    {
      status = execute_it(shell->trees[i], shell);
      shell->ret = status;
      close_fds(shell->trees[i]);
      free_tree(shell->trees[i]);
      ++i;
    }
  free(shell->trees);
  return (status);
}
