/*
** free_tab.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src/utils
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 14:30:34 2016 Matteo
** Last update Wed Oct 19 14:32:06 2016 Matteo
*/

#include <stdlib.h>

void		free_tab(char **tab)
{
  int		i;

  i = -1;
  while (tab[++i])
    free(tab[i]);
  free(tab);
}
