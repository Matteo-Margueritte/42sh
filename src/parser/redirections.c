/*
** redirections.c for 42sh in /home/matteo/rendu/test/parseur
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 12:05:01 2016 Matteo
** Last update Sun Oct 23 14:39:03 2016 Matteo
*/

#include <string.h>
#include "parser.h"

int		redir_exp(t_node **tree, t_token *token)
{
  int		save;

  save = token->i;
  if (redir_left_norm(tree, token) == FAILURE)
    {
      token->i = save;
      if (!redir_left_spe(tree, token))
	return (FAILURE);
    }
  return (SUCCESS);
}

int		redir_left_norm(t_node **tree, t_token *token)
{
  int		save;
  t_node	*new;

  if (redir_right(tree, token) == SUCCESS)
    {
      if (token->tab[token->i] != NULL)
	if (is_left_redir(token->tab[token->i]) == SUCCESS)
	  {
	    if ((new = create_node()) == NULL)
	      return (FAILURE);
	    new->type = (!strcmp(token->tab[token->i], DR_LEFT))
	      ? LEFT : D_LEFT;
	    new->left = *tree;
	    *tree = new;
	    token->i++;
	    save = file_exp(&(new->right), token);
	    while (cmd_exp(token) == SUCCESS && token->i++);
	    return ((is_right_redir(token->tab[token->i]) == SUCCESS)
		    ? special_case(tree, token) : save);
	  }
      return (SUCCESS);
    }
  return (FAILURE);
}

int		redir_left_spe(t_node **tree, t_token *token)
{
  int		ret;
  t_node	*new;

  if (is_left_redir(token->tab[token->i++]) == SUCCESS)
    if (file_exp(tree, token) == SUCCESS)
      {
	if ((new = create_node()) == NULL)
	  return (FAILURE);
	new->type = (!strcmp(token->tab[token->i - 2], DR_LEFT))
	  ? LEFT : D_LEFT;
	new->right = *tree;
	*tree = new;
	ret = command_exp(&(new->left), token);
	return ((is_right_redir(token->tab[token->i]) == SUCCESS)
		    ? special_case(tree, token) : ret);
      }
  return (FAILURE);
}

int		redir_right(t_node **tree, t_token *token)
{
  int		save;

  save = token->i;
  if (redir_right_norm(tree, token) == FAILURE)
    {
      token->i = save;
      if (redir_right_spe(tree, token) == FAILURE)
	return (FAILURE);
    }
  return (SUCCESS);
}

int		redir_right_norm(t_node **tree, t_token *token)
{
  int		status;
  t_node	*new;

  if (command_exp(tree, token) == SUCCESS)
    {
      if (token->tab[token->i] != NULL)
	if (is_right_redir(token->tab[token->i]) == SUCCESS)
	  {
	    if ((new = create_node()) == NULL)
	      return (FAILURE);
	    new->type = (strcmp(token->tab[token->i], DR_RIGHT) != 0)
	      ? RIGHT : D_RIGHT;
	    new->left = *tree;
	    *tree = new;
	    token->i++;
	    status = file_exp(&(new->right), token);
	    while (cmd_exp(token) == SUCCESS && token->i++);
	    return (status);
	  }
      return (SUCCESS);
    }
  return (FAILURE);
}
