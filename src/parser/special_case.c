/*
** special_case.c for 42sh in /home/matteo/rendu/test/parseur
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 12:06:56 2016 Matteo
** Last update Wed Oct 19 12:12:04 2016 Matteo
*/

#include <string.h>
#include "parser.h"

int		special_case(t_node **tree, t_token *token)
{
  t_node	*new;

  if ((new = create_node()) == NULL)
    return (FAILURE);
  new->type = (!strcmp(token->tab[token->i], DR_RIGHT))
    ? D_RIGHT : RIGHT;
  new->left = *tree;
  *tree = new;
  token->i++;
  return (file_exp(&(new->right), token));
}
