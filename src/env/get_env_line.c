/*
** get_env_line.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src/env
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 14:10:41 2016 Matteo
** Last update Sun Oct 23 01:02:32 2016 Matteo
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"

static char	*get_data(char *str)
{
  char		*res;
  int		i;
  int		j;

  i = 0;
  j = 0;
  if ((res = malloc(sizeof(char) * strlen(str))) == NULL)
    return (NULL);
  while (str[i] != '=')
    i++;
  i++;
  while (str[i])
    {
      res[j] = str[i];
      j++;
      i++;
    }
  res[j] = 0;
  return (res);
}

char		*get_env_line(char *key)
{
  t_env		*tmp;

  tmp = g_env;
  while (tmp)
    {
      if (strncmp(key, tmp->env_line, strlen(key)) == 0)
	return (get_data(tmp->env_line));
      tmp = tmp->next;
    }
  if (strcmp(key, "PATH") != SUCCESS)
    fprintf(stderr, "Couldn't find %s environnement variable.\n", key);
  return (NULL);
}
