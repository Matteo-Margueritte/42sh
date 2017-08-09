/*
** parser.c for 42sh in /home/matteo/rendu/test/parseur
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 11:56:04 2016 Matteo
** Last update Sat Oct 22 17:06:40 2016 Matteo
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "parser.h"

t_node		*create_node()
{
  t_node	*new;

  if ((new = malloc(sizeof(t_node))) == NULL)
    return (NULL);
  new->fd_in = 0;
  new->fd_out = 1;
  new->path = NULL;
  new->args = NULL;
  new->type = UNKNOWN;
  new->left = NULL;
  new->right = NULL;
  return (new);
}

static t_node	*fill_node(char *command)
{
  t_token	token;
  t_node	*current;

  if ((token.tab = my_str_to_wordtab(command, ' ')) == NULL)
    return (NULL);
  token.i = 0;
  if (expression(&current, &token) != SUCCESS)
    fprintf(stderr, "42sh: error while building the command tree\n");
  free_tab(token.tab);
  return (current);
}

t_node		**parser(char *command_line)
{
  char		**commands;
  t_node	**trees;
  int		i;

  i = 0;
  if ((commands = my_str_to_wordtab(command_line, ';')) == NULL)
    return (NULL);
  while (commands[i])
    ++i;
  if ((trees = malloc(sizeof(t_node) * (i + 1))) == NULL)
    return (NULL);
  i = -1;
  while (commands[++i])
    if ((trees[i] = fill_node(commands[i])) == NULL)
      return (NULL);
  trees[i] = NULL;
  free_tab(commands);
  return (trees);
}
