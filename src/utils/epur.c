/*
** epur.c for epur.c in /home/lak_r/rendu/PSU_2015_42sh/src/utils
** 
** Made by lak remi
** Login   <lak_r@epitech.net>
** 
** Started on  Mon Oct 24 18:01:24 2016 lak remi
** Last update Mon Oct 24 19:51:41 2016 lak remi
*/

#include <stdlib.h>

static int	my_strlen(char *str)
{
  int		i;

  i = 0;
  while (str[i] != 0)
    i++;
  return (i);
}

static int	is_blank(char c)
{
  return ((c == ' ' || c == '\t') ? 1 : 0);
}

char		*epur(char *str)
{
  int		i;
  int		k;
  char		*new;

  i = 0;
  k = 0;
  if (!(new = malloc(sizeof(char) * my_strlen(str))))
    return (NULL);
  while (str[i] != 0)
    {
      while (str[i] != 0 && is_blank(str[i]) == 1)
	i++;
      while (str[i] != 0 && is_blank(str[i]) == 0)
	new[k++] = str[i++];
      while (str[i] != 0 && is_blank(str[i]) == 1)
	i++;
      if (str[i] != 0)
	new[k++] = ' ';
    }
  new[k] = 0;
  return (new);
}
