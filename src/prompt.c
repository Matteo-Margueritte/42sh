/*
** prompt.c for 42 in /home/matteo/rendu/PSU_2015_42sh/src
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 15:12:58 2016 Matteo
** Last update Fri Nov  4 12:39:56 2016 Solfurie
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include "utils.h"
#include "parser.h"
#include "get_next_line.h"

static int	check_path(char pwd[PATH_MAX])
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (pwd[i])
    {
      if (pwd[i] == '/')
	j++;
      if (j > 2)
	return (i);
      i++;
    }
  return (j);
}

static int	print_user()
{
  struct passwd	*use;
  uid_t		id;

  dprintf(STDIN_FILENO, "%s", BOLD);
  dprintf(STDIN_FILENO, "%s", CYAN);
  id = getuid();
  if ((use = getpwuid(id)) == NULL)
    return (FAILURE);
  dprintf(STDIN_FILENO, "%s", use->pw_name);
  dprintf(STDIN_FILENO, "%s", RED);
  dprintf(STDIN_FILENO, "@");
  return (SUCCESS);
}

void		print_prompt(int signum)
{
  char		pwd[PATH_MAX];
  int		s;

  if (signum == SIGINT)
    dprintf(STDIN_FILENO, "\n");
  if (print_user() == FAILURE)
    return ;
  dprintf(STDIN_FILENO, "%s", ORANGE);
  if (getcwd(pwd, PATH_MAX) != NULL)
    {
      s = check_path(pwd);
      if (s < 2)
	dprintf(STDIN_FILENO, "%s", pwd);
      else if (s == 2 || s == 3)
	dprintf(STDIN_FILENO, "~");
      else
	dprintf(STDIN_FILENO, "%s", pwd + s + 1);
    }
  dprintf(STDIN_FILENO, "%s", MAGENTA);
  dprintf(STDIN_FILENO, " > ");
  dprintf(STDIN_FILENO, "%s", RESET);
}

int		prompt(t_shell *shell)
{
  int		status;
  char		*input;

  status = 0;
  print_prompt(0);
  while (shell->exit_status == -1 &&
	 (input = get_next_line(0)) != NULL)
    {
      if (input[0] != '\0' && check_syntax(input) == SUCCESS)
	{
	  if (put_in_history(input, shell) == FAILURE
	      || (shell->trees = parser(input)) == NULL)
	    return (FAILURE);
	  status = main_execution(shell);
	}
      free(input);
      if (shell->exit_status == -1)
	print_prompt(0);
    }
  if (shell->exit_status == -1 && input != NULL)
    printf("\n");
  return ((shell->exit_status == -1) ? status : shell->exit_status);
}
