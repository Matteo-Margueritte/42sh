/*
** fd_handlers.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src/execution/utils
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 14:47:46 2016 Matteo
** Last update Sat Oct 22 00:01:16 2016 Matteo
*/

#include <unistd.h>
#include "parser.h"

void	set_fd_out(t_node *current, const int fd)
{
  if (current != NULL && current->type != CMD)
    {
      if (current->right->type == CMD)
	set_fd_out(current->right, fd);
      else
	set_fd_out(current->left, fd);
    }
  else if (current != NULL && current->type == CMD)
    current->fd_out = fd;
}

void	set_fd_in(t_node *current, const int fd)
{
  if (current != NULL && current->type != CMD)
    {
      if (current->right->type == CMD)
	set_fd_in(current->right, fd);
      else
	set_fd_in(current->left, fd);
    }
  else if (current != NULL && current->type == CMD)
    current->fd_in = fd;
}

void		close_fds(t_node *current)
{
  if (current == NULL)
    return ;
  if (current->fd_in != 0)
    {
      close(current->fd_in);
      current->fd_in = 0;
    }
  if (current->fd_out != 1)
    {
      close(current->fd_out);
      current->fd_out = 1;
    }
  close_fds(current->left);
  close_fds(current->right);
}
