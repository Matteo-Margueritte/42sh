/*
** execute_pipes.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src/execution
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 18:03:04 2016 Matteo
** Last update Mon Oct 24 21:55:09 2016 Matteo
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "builtin.h"
#include "utils.h"

static int	clean_execve(t_node *current, char **env, t_shell *shell,
			     int fd_to_close)
{
  close(fd_to_close);
  if (dup2(current->fd_in, 0) == -1 || dup2(current->fd_out, 1) == -1)
    return (FAILURE);
  if (execve(current->path, current->args, env) == -1)
    {
      fprintf(stderr, "%s%s", current->args[0], EXEC_ERR);
      my_exit(NULL, shell);
      return (FAILURE);
    }
  return (SUCCESS);
}

static int	execution_chain(t_node *tree, t_shell *shell)
{
  if (tree->type == T_PIPE)
    return (execute_simple_pipe(tree, shell));
  else if (tree->type == CMD)
    return (simple_exec(tree, shell));
  else if (tree->type == D_RIGHT || tree->type == RIGHT)
    return (right_redirection(tree, shell));
  return (SUCCESS);
}

int		execute_simple_pipe(t_node *tree, t_shell *shell)
{
  int		fd[2];
  t_node	*cmd;
  pid_t		pid;

  cmd = tree->right;
  if (pipe(fd) == -1)
    return (FAILURE);
  set_fd_out(tree->right, fd[1]);
  set_fd_in(tree->left, fd[0]);
  cmd->path = get_good_path(cmd->args[0]);
  if ((shell->env_tab = list_to_tab(g_env)) == NULL)
    return (FAILURE);
  if (cmd->path != NULL)
    {
      pid = fork();
      if (pid == 0)
	if (clean_execve(cmd, shell->env_tab, shell, fd[0]) == FAILURE)
	  return (FAILURE);
    }
  close(fd[1]);
  free(shell->env_tab);
  cmd->fd_out = 1;
  return (execution_chain(tree->left, shell));
}

int		init_first_pipe_spe(t_node *tree, t_shell *shell, int *fd)
{
  t_node	*cmd;
  pid_t		pid;

  if (spe_left(tree->right) == FAILURE || (pid = fork()) == -1)
    return (FAILURE);
  cmd = tree->right->left;
  if (pid == 0)
    {
      if ((shell->env_tab = list_to_tab(g_env)) == NULL ||
	  (cmd->path = get_good_path(cmd->args[0])) == NULL)
	my_exit(NULL, shell);
      if (clean_execve(cmd, shell->env_tab, shell, fd[0]) == FAILURE)
	return (FAILURE);
    }
  close(fd[1]);
  cmd->fd_out = 1;
  if (execution_chain(tree->left, shell) != SUCCESS)
    return (FAILURE);
  return (SUCCESS);
}

int		prepare_pipes(t_node *tree, t_shell *shell)
{
  int		fd[2];
  int		status;

  status = SUCCESS;
  if (pipe(fd) == -1)
    return (FAILURE);
  if (tree->right->type == CMD)
    status = execute_simple_pipe(tree, shell);
  else
    {
      set_fd_out(tree->right, fd[1]);
      set_fd_in(tree->left, fd[0]);
      status = init_first_pipe_spe(tree, shell, fd);
    }
  return (status);
}
