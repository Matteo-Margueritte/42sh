/*
** simple_command.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src/execution
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 15:02:05 2016 Matteo
** Last update Mon Oct 24 22:55:35 2016 Matteo
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "parser.h"
#include "utils.h"
#include "builtin.h"

static int	check_status(int status)
{
  if (WIFEXITED(status))
    return (WEXITSTATUS(status));
  else if (WIFSIGNALED(status))
    {
      if (WTERMSIG(status) == 11 || WTERMSIG(status) == 139)
	{
	  if (WCOREDUMP(status))
	    fprintf(stderr, "Segmentation fault (core dumped)\n");
	  else
	    fprintf(stderr, "Segmentation fault\n");
	  return (139);
	}
      else if (WTERMSIG(status) == 8 || WTERMSIG(status) == 136)
	{
	  if (WCOREDUMP(status))
	    fprintf(stderr, "Floating exception (core dumped)\n");
	  else
	    fprintf(stderr, "Floating exception\n");
	  return (136);
	}
    }
  return (status);
}

static int	child_process(t_node *current, char **env, t_shell *shell)
{
  dup2(current->fd_in, 0);
  dup2(current->fd_out, 1);
  if (execve(current->path, current->args, env) == -1)
    {
      fprintf(stderr, "%s%s", current->args[0], EXEC_ERR);
      my_exit(NULL, shell);
      return (FAILURE);
    }
  return (SUCCESS);
}

int		simple_exec(t_node *tree, t_shell *shell)
{
  int		status;
  pid_t		pid;

  if (check_builtin(tree->args[0]) == SUCCESS)
    return (exec_builtin(tree->args, shell));
  if ((tree->path = get_good_path(tree->args[0])) == NULL ||
      (shell->env_tab = list_to_tab(g_env)) == NULL)
       return (FAILURE);
  status = 0;
  pid = fork();
  if (pid == 0)
    {
      if (child_process(tree, shell->env_tab, shell) == FAILURE)
	return (FAILURE);
    }
  else if (pid > 0)
    if (waitpid(pid, &status, 0) == -1)
      fprintf(stderr, "Error wait\n");
  status = check_status(status);
  free(shell->env_tab);
  return (status);
}
