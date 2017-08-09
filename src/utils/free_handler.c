/*
** free_handler.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src/utils
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Fri Oct 21 00:54:59 2016 Matteo
** Last update Mon Oct 24 22:48:34 2016 Matteo
*/

#include <stdlib.h>
#include "utils.h"

void		free_tree(t_node *node)
{
  if (node->right != NULL)
    free_tree(node->right);
  if (node->left != NULL)
    free_tree(node->left);
  if (node->path != NULL)
    free(node->path);
  if (node->args != NULL)
    free_tab(node->args);
  free(node);
}

void		free_env(t_env *head)
{
  t_env		*tmp;
  t_env		*tmp1;

  tmp = head;
  while (tmp != NULL)
    {
      tmp1 = tmp;
      tmp = tmp->next;
      free(tmp1->env_line);
      free(tmp1);
    }
}

void		free_alias(t_alias *head)
{
  t_alias	*tmp;
  t_alias	*tmp1;

  tmp = head;
  while (tmp != NULL)
    {
      tmp1 = tmp;
      tmp = tmp->next;
      free_tab(tmp1->cmd);
      free(tmp1->alias);
      free(tmp1);
    }
}
