/*
** get_next_line.c for getnextline in /home/vidal_s/rendu/CPE_tek1/CPE_2015_getnextline
**
** Made by sebastien vidal
** Login   <vidal_s@epitech.net>
**
** Started on  Fri Jun 17 17:04:11 2016 sebastien vidal
** Last update Wed Oct 19 15:38:52 2016 Matteo
*/

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static char	*my_realloc(char *str, int size)
{
  char		*tmp;
  int		i;

  i = 0;
  if (!(tmp = malloc(sizeof(char) * size)))
    return (NULL);
  while (i < (size - (READ_SIZE + 1)))
    {
      tmp[i] = str[i];
      i = i + 1;
    }
  free(str);
  return (tmp);
}

static char	get_char(const int fd)
{
  static int	pos = 0;
  static char	*pt;
  static char	buff[READ_SIZE];
  char		c;

  if (pos == 0)
    {
      if ((pos = read(fd, buff, READ_SIZE)) == -1)
	return (-1);
      pt = &buff[0];
      if (pos == 0)
	return (0);
    }
  if (fd < 0)
    return (-1);
  c = *pt;
  pt = pt + 1;
  pos = pos - 1;
  return (c);
}

static int	check_end(char c, char *str)
{
  if (c == 0 && str[0] == 0)
    {
      free(str);
      return (1);
    }
  return (0);
}

char		*get_next_line(const int fd)
{
  char		c;
  char		*str;
  int		i;

  i = 0;
  if (!(str = malloc(sizeof(char) * READ_SIZE + 1)))
    return (NULL);
  if ((c = get_char(fd)) == -1)
    return (NULL);
  while (c != '\n' && c != '\0')
    {
      str[i] = c;
      if ((c = get_char(fd)) == -1)
	return (NULL);
      i = i + 1;
      if (i % (READ_SIZE + 1) == 0)
	{
	  if ((str = my_realloc(str, i + READ_SIZE + 1)) == NULL)
	    return (NULL);
	}
    }
  str[i] = '\0';
  if (check_end(c, str) == 1)
    return (NULL);
  return (str);
}
