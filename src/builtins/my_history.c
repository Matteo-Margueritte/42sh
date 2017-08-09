/*
** my_history.c for 42sh in /home/gayrau_a/rendu_tek1/S2/PSU/PSU_2015_42sh/src/builtins
**
** Made by gayrau_a
** Login   <gayrau_a@epitech.net>
**
** Started on  Sun Oct 23 22:45:00 2016 gayrau_a
** Last update Wed Dec 21 10:19:25 2016 Matteo
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include "builtin.h"
#include "get_next_line.h"

int		fill_empty_history(t_shell *shell)
{
  int		i;

  i = 0;
  while (i <= MAX_HIST)
    {
      shell->hist[i] = NULL;
      i = i + 1;
    }
  return (SUCCESS);
}

int		fill_history(t_shell *shell, char *str, int *i)
{
  int		u;
  int		y;

  u = 0;
  y = 0;
  while (str[u] >= '0' && str[u] <= '9')
    u = u + 1;
  u = u + 1;
  if ((shell->hist[*i] = malloc(sizeof(char) * strlen(str))) == NULL)
    return (FAILURE);
  while (str[u])
    {
      shell->hist[*i][y] = str[u];
      u = u + 1;
      y = y + 1;
    }
  shell->hist[*i][y] = '\0';
  *i = *i + 1;
  return (*i);
}

int		read_history(t_shell *shell)
{
  int		fd;
  char		*str;
  int		i;

  i = 0;
  if ((fd = open(HISTORY, O_RDONLY)) > 0)
    {
      while ((str = get_next_line(fd)) != NULL)
	{
	  fill_history(shell, str, &i);
	  free(str);
	}
      while (i <= MAX_HIST)
	{
	  shell->hist[i] = NULL;
	  i = i + 1;
	}
    }
  else
    fill_empty_history(shell);
  return (SUCCESS);
}

int		realloc_tab(t_shell *shell)
{
  int		i;

  i = 0;
  while (shell->hist[i])
    {
      if (shell->hist[i + 1] != NULL)
	{
	  free(shell->hist[i]);
	  if ((shell->hist[i] = strdup(shell->hist[i + 1])) == NULL)
	    return (FAILURE);
	}
      i = i + 1;
    }
  return (SUCCESS);
}

int		put_in_history(char *str, t_shell *shell)
{
  static int	i;

  if (MAX_HIST <= 10)
    return (FAILURE);
  while (shell->hist[i])
    i++;
  if (i < MAX_HIST - 1)
    {
      if ((shell->hist[i] = strdup(str)) == NULL)
	return (FAILURE);
      i = i + 1;
    }
  else
    {
      if ((realloc_tab(shell)) == FAILURE)
	return (FAILURE);
      free(shell->hist[MAX_HIST - 1]);
      if ((shell->hist[MAX_HIST - 1] = strdup(str)) == NULL)
	return (FAILURE);
    }
  return (SUCCESS);
}
