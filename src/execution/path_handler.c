/*
** path_handler.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src/execution
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 15:43:15 2016 Matteo
** Last update Sun Oct 23 15:57:52 2016 Matteo
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "utils.h"
#include "shell.h"

char		**get_all_path()
{
  char		*path;
  char		**path_tab;

  if ((path = get_env_line("PATH")) == NULL)
    {
      if ((path_tab = my_str_to_wordtab(DEFAULT_PATH, ':')) == NULL)
	return (NULL);
    }
  else
    if ((path_tab = my_str_to_wordtab(path, ':')) == NULL)
      return (NULL);
  free(path);
  return (path_tab);
}

int		check_if_dir(char *path)
{
  struct stat	path_stat;

  if (stat(path, &path_stat) == -1)
    return (FAILURE);
  if ((path_stat.st_mode & S_IFMT) == S_IFDIR)
    return (FAILURE);
  return (SUCCESS);
}

char		*get_r_path(char *command)
{
  char		*good_path;

  good_path = strdup(command);
  if (access(command, F_OK) == SUCCESS && access(command, X_OK) == SUCCESS)
    {
      if (check_if_dir(good_path) == FAILURE)
	{
	  if (strchr(command, '/') != NULL)
	    fprintf(stderr, "%s: Permission denied.\n", command);
	  else
	    fprintf(stderr, "%s: Command not found.\n", command);
	  free(good_path);
	  return (NULL);
	}
      return (good_path);
    }
  free(good_path);
  fprintf(stderr, "%s: Command not found.\n", command);
  return (NULL);
}

static char	*format_path(char *path, char *command)
{
  char		*good_path;

  if (strcmp(path, "/") == 0)
    {
      fprintf(stderr, "%s: Command not found.\n", command);
      return (NULL);
    }
  if ((good_path = strdup(path)) == NULL ||
      (good_path = realloc(good_path, sizeof(char) *
			   (strlen(good_path) + 2))) == NULL ||
      (good_path = strcat(good_path, "/")) == NULL ||
      (good_path =
       realloc(good_path, sizeof(char) *
	       (strlen(command) + strlen(good_path) + 1))) == NULL ||
      (good_path = strcat(good_path, command)) == NULL)
    return (NULL);
  return (good_path);
}

char		*get_good_path(char *command)
{
  char		*good_path;
  char		**path_tab;
  int		i;

  i = -1;
  if ((path_tab = get_all_path()) == NULL)
    return (NULL);
  while (path_tab[++i])
    {
      if ((good_path = format_path(path_tab[i], command)) == NULL)
	return (NULL);
      if (access(good_path, F_OK) == 0 && access(good_path, X_OK) == 0
	  && check_if_dir(good_path) == SUCCESS)
	{
	  free_tab(path_tab);
	  return (good_path);
	}
      free(good_path);
    }
  free_tab(path_tab);
  return (get_r_path(command));
}
