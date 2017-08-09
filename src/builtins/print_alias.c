/*
** print_alias.c for alias in /home/nagamo_s/rendu/PSU_2015_42sh/src/builtins
**
** Made by stephane
** Login   <nagamo_s@epitech.net>
**
** Started on  Mon Oct 24 18:33:30 2016 stephane
** Last update Mon Oct 24 19:06:03 2016 stephane
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

static void	print_one_alias(t_shell *shell, char **tab)
{
  int		i;

  i = 0;
  while (strcmp(tab[1], shell->list_alias->alias)
	 != 0 && shell->list_alias->next != NULL)
    shell->list_alias =  shell->list_alias->next;
  if (strcmp(tab[1], shell->list_alias->alias) == 0)
    {
      while (shell->list_alias->cmd[i] != NULL)
	printf("%s ", shell->list_alias->cmd[i++]);
      printf("\n");
    }
}

static void	all_alias(t_shell *shell)
{
  int		i;

  i = 0;
  printf("%s\t", shell->list_alias->alias);
  if (shell->list_alias->cmd[i + 1] != NULL)
    {
      printf("(");
      while (shell->list_alias->cmd[i] != NULL)
	printf("%s ", shell->list_alias->cmd[i++]);
      printf("\b)\n");
    }
  else
    {
      while (shell->list_alias->cmd[i] != NULL)
	printf("%s ", shell->list_alias->cmd[i++]);
      printf("\n");
    }
}

static void	print_all_alias(t_shell *shell)
{
  while (shell->list_alias->next != NULL)
    {
      all_alias(shell);
      shell->list_alias = shell->list_alias->next;
    }
  all_alias(shell);
  while (shell->list_alias->prev != NULL)
    shell->list_alias = shell->list_alias->prev;
}

void		print_alias(t_shell *shell, char **tab)
{
  if (shell->list_alias == NULL)
    return ;
  if (tab[1] == NULL)
    print_all_alias(shell);
  else
    print_one_alias(shell, tab);
}
