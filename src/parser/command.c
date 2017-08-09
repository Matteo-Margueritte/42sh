/*
** command.c for 42sh in /home/matteo/rendu/test/parseur
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Tue Oct 18 22:30:43 2016 Matteo
** Last update Wed Oct 19 12:24:24 2016 Matteo
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

static char	**tab_cpy(char **src, int len)
{
  int		i;
  char		**dest;

  i = 0;
  dest = NULL;
  if (!(dest = malloc((len + 1) * sizeof(*dest))))
    return (NULL);
  while (i < len)
    {
      if (!(dest[i] = strdup(src[i])))
	return (NULL);
      i++;
    }
  dest[i] = NULL;
  return (dest);
}

int		command_exp(t_node **tree, t_token *token)
{
  t_node	*new;

  if (cmd_exp(token) == SUCCESS)
    {
      new = create_node();
      new->type = CMD;
      new->cmd_len = 1;
      new->address_tmp = &(token->tab[token->i++]);
      while (cmd_exp(token) == SUCCESS && token->i++)
	new->cmd_len++;
      if (!(new->args = tab_cpy(new->address_tmp, new->cmd_len)))
	return (FAILURE);
      *tree = new;
      return (SUCCESS);
    }
  return (FAILURE);
}

int		cmd_exp(t_token *token)
{
  if (token->tab[token->i] != NULL &&
      is_redir_or_sep(token->tab[token->i]) == FAILURE)
    return (SUCCESS);
  return (FAILURE);
}

int		file_exp(t_node **tree, t_token *token)
{
  t_node	*new;

  if (is_redir_or_sep(token->tab[token->i]) == FAILURE)
    {
      new = create_node();
      new->type = T_FILE;
      new->cmd_len = 1;
      new->address_tmp = &(token->tab[token->i++]);
      if (!(new->args = tab_cpy(new->address_tmp, new->cmd_len)))
	return (FAILURE);
      *tree = new;
      return (SUCCESS);
    }
  return (FAILURE);
}
