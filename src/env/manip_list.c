/*
** manip_list.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src/env
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 14:12:59 2016 Matteo
** Last update Sat Oct 22 23:50:33 2016 Matteo
*/

#include <string.h>
#include <stdlib.h>
#include "shell.h"

static t_env	*create_elem(char *line)
{
  t_env		*elem;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    return (NULL);
  if ((elem->env_line = strdup(line)) == NULL)
    return (NULL);
  elem->next = NULL;
  return (elem);
}

static t_env	*create_empty_env()
{
  t_env		*list;

  if ((list = malloc(sizeof(*list))) == NULL)
    return (NULL);
  list->env_line = strdup(DEFAULT_PATH);
  list->next = NULL;
  return (list);
}

t_env		*create_env(char **env)
{
  t_env		*tmp;
  t_env		*list;
  t_env		*elem;
  int		i;

  i = 1;
  if (env == NULL || env[0] == NULL)
    return (((list = create_empty_env()) == NULL) ? NULL : list);
  if ((list = create_elem(env[0])) == NULL)
    return (NULL);
  tmp = list;
  while (env[i])
    {
      if ((elem = create_elem(env[i])) == NULL)
	return (NULL);
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = elem;
      i++;
    }
  return (list);
}
