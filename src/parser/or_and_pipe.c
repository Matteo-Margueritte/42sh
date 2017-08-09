/*
** or_and_pipe.c for 42sh in /home/matteo/rendu/test/parseur
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 12:00:44 2016 Matteo
** Last update Sun Oct 23 14:39:27 2016 Matteo
*/

#include <string.h>
#include "parser.h"

int		expression(t_node **tree, t_token *token)
{
  return (or_exp(tree, token));
}

int		or_exp(t_node **tree, t_token *token)
{
  t_node	*new;

  if (and_exp(tree, token) == SUCCESS)
    {
      if (token->tab[token->i] != NULL)
	if (strcmp(token->tab[token->i], OR) == 0)
	  {
	    token->i++;
	    if ((new = create_node()) == NULL)
	      return (FAILURE);
	    new->type = T_OR;
	    new->left = *tree;
	    *tree = new;
	    return (or_exp(&(new->right), token));
	  }
	else
	  return (FAILURE);
      else
	return (SUCCESS);
    }
  return (FAILURE);
}

int		and_exp(t_node **tree, t_token *token)
{
  t_node	*new;

  if (pipe_exp(tree, token) == SUCCESS)
    {
      if (token->tab[token->i] != NULL)
	if (strcmp(token->tab[token->i], AND) == 0)
	    {
	      token->i++;
	      if ((new = create_node()) == NULL)
		return (FAILURE);
	      new->type = T_AND;
	      new->left = *tree;
	      *tree = new;
	      return (and_exp(&(new->right), token));
	    }
      return (SUCCESS);
    }
  return (FAILURE);
}

int		pipe_exp(t_node **tree, t_token *token)
{
  t_node	*new;

  if (redir_exp(tree, token) == SUCCESS)
    {
      if (token->tab[token->i] != NULL)
	if (strcmp(token->tab[token->i], PIPE) == 0)
	  {
	    token->i++;
	    if ((new = create_node()) == NULL)
	      return (FAILURE);
	    new->type = T_PIPE;
	    new->right = *tree;
	    *tree = new;
	    return (pipe_exp(&(new->left), token));
	  }
      return (SUCCESS);
    }
  return (FAILURE);
}

int		redir_right_spe(t_node **tree, t_token *token)
{
  t_node	*new;

  if (is_right_redir(token->tab[token->i++]) == SUCCESS)
    if (file_exp(tree, token) == SUCCESS)
      {
	if ((new = create_node()) == NULL)
	  return (FAILURE);
	new->type = (!strcmp(token->tab[token->i - 2], DR_RIGHT))
	  ? RIGHT : D_RIGHT;
	new->right = *tree;
	*tree = new;
	return (command_exp(&(new->left), token));
      }
  return (FAILURE);
}
