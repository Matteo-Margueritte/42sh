/*
** my_unsetenv.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src/env
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 14:16:10 2016 Matteo
** Last update Sun Oct 23 14:30:58 2016 Matteo
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "shell.h"

static int	check_arg_unsetenv(char **arg)
{
  int		i;

  i = 0;
  while (arg[i])
    i++;
  if (i < 2)
    {
      fprintf(stderr, "unsetenv: Too few arguments.\n");
      return (FAILURE);
    }
  return (SUCCESS);
}

static void	erase_env_list(t_env **to_del, t_env **head)
{
  t_env		*tmp;
  t_env		*tmp_next;

  tmp_next = (*to_del)->next;
  if (*to_del == *head)
    {
      (*head) = tmp_next;
      free((*to_del)->env_line);
      free(*to_del);
      *to_del = NULL;
      return ;
    }
  tmp = (*head);
  while (tmp->next != (*to_del))
    tmp = tmp->next;
  tmp->next = (*to_del)->next;
  free((*to_del)->env_line);
  free((*to_del));
  *to_del = tmp_next;
}

int		my_unsetenv(char **arg, t_shell *shell)
{
  t_env		*tmp;
  char		*tmp_l;
  int		i;
  int		len;

  i = 0;
  (void)shell;
  if (check_arg_unsetenv(arg) == FAILURE)
    return (FAILURE);
  while (arg[++i])
    {
      tmp = g_env;
      while (tmp != NULL)
	{
	  len = -1;
	  while (tmp->env_line[++len] != '=' && tmp->env_line[len] != '\0');
	  tmp_l = cut_str(tmp->env_line, len);
	  if (strcmp(arg[i], tmp_l) == SUCCESS)
	    erase_env_list(&tmp, &g_env);
	  else
	    tmp = tmp->next;
	  free(tmp_l);
	}
    }
  return (FAILURE);
}

int		my_env(char **args, t_shell *shell)
{
  t_env		*tmp;

  (void)shell;
  tmp = g_env;
  if (args != NULL)
    if (args[1] != NULL)
      return (FAILURE);
  while (tmp != NULL)
    {
      if (tmp->env_line != NULL)
	printf("%s\n", tmp->env_line);
      tmp = tmp->next;
    }
  return (SUCCESS);
}
