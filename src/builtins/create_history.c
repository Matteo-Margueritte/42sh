/*
** create_history.c for 42sh in /home/vidal_s/work/history
**
** Made by sebastien vidal
** Login   <vidal_s@epitech.net>
**
** Started on  Sun Oct 23 23:32:13 2016 sebastien vidal
** Last update Wed Dec 21 10:27:57 2016 Matteo
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include "shell.h"

int		my_history(char **tab, t_shell *shell)
{
  int		i;
  int		nb;

  i = 0;
  nb = 1;
  (void)tab;
  while (shell->hist[i])
    {
      printf("%d %s\n", nb, shell->hist[i]);
      i = i + 1;
      nb = nb + 1;
    }
  return (SUCCESS);
}

int		write_history(t_shell *shell)
{
  int		fd;
  int		i;

  i = 0;
  if ((fd = open(HISTORY, O_CREAT | O_RDWR | O_TRUNC , S_IRWXU)) == -1)
    return (FAILURE);
  while (shell->hist[i])
    {
      dprintf(fd, "%d %s\n", i + 1, shell->hist[i]);
      free(shell->hist[i]);
      i++;
    }
  return (SUCCESS);
}
