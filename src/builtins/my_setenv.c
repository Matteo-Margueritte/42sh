/*
** my_setenv.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src/env
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 14:15:56 2016 Matteo
** Last update Mon Oct 24 18:09:34 2016 Matteo
*/

#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "builtin.h"

static int	check_arg_setenv(char **arg)
{
  int		i;

  i = -1;
  while (arg[++i]);
  if (i > 3)
    {
      fprintf(stderr, "setenv: Too many arguments.\n");
      return (FAILURE);
    }
  i = -1;
  while (arg[1][++i] != '\0')
    if ((arg[1][i] < 'a' || arg[1][i] > 'z') &&
	(arg[1][i] < 'A' || arg[1][i] > 'Z') &&
	(arg[1][i] < '0' || arg[1][i] > '9') &&
	arg[1][i] != '_')
      {
	fprintf(stderr, "setenv: Variable name must"
		" contain alphanumeric characters.\n");
	return (FAILURE);
      }
  return (SUCCESS);
}

static int	modify_env_list(char **arg, t_env **elem, int var_len,
				char *to_free)
{
  free(to_free);
  if (arg[2] == NULL)
    return (SUCCESS);
  if (((*elem)->env_line =
       realloc((*elem)->env_line,
	       sizeof(char) *
	       (strlen(arg[2]) + var_len + 1))) == NULL)
    return (FAILURE);
  (*elem)->env_line[var_len] = '\0';
  (*elem)->env_line = strcat((*elem)->env_line, arg[2]);
  return (SUCCESS);
}

static char	*create_line(char **arg)
{
  char		*result;

  result = strdup(arg[1]);
  if ((result =
       realloc(result, sizeof(char) * (strlen(result) + 2))) == NULL)
    return (NULL);
  result = strcat(result, "=");
  if (arg[2] != NULL)
    {
      if ((result =
	   realloc(result, sizeof(char) *
		  (strlen(result) + strlen(arg[2]) + 1))) == NULL)
	return (NULL);
      result = strcat(result, arg[2]);
    }
  return (result);
}

static int	add_env_list(char **arg)
{
  t_env		*tmp;
  t_env		*elem;

  tmp = g_env;
  if (tmp != NULL)
    while (tmp->next != NULL)
      tmp = tmp->next;
  if (((elem = malloc(sizeof(*elem))) == NULL) ||
      ((elem->env_line = create_line(arg)) == NULL))
    return (FAILURE);
  elem->next = NULL;
  if (tmp != NULL)
    tmp->next = elem;
  else
    g_env = elem;
  return (SUCCESS);
}

int		my_setenv(char **arg, t_shell *shell)
{
  t_env		*tmp;
  int		len;
  char		*tmp_l;

  tmp = g_env;
  (void)shell;
  if (check_arg_setenv(arg) == FAILURE)
    return (FAILURE);
  if (arg[1] == NULL)
    return (my_env(NULL, NULL));
  while (tmp != NULL)
    {
      len = -1;
      while (tmp->env_line[++len] != '=' && tmp->env_line[len] != '\0');
      tmp_l = cut_str(tmp->env_line, len);
      if (strcmp(arg[1], tmp_l) == 0)
	return ((modify_env_list(arg, &tmp, len + 1, tmp_l) == FAILURE)
		? FAILURE : SUCCESS);
      free(tmp_l);
      tmp = tmp->next;
    }
  if (add_env_list(arg) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}
