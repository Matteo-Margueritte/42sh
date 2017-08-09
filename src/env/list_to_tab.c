/*
** list_to_tab.c for 42sh in /home/vidal_s/rendu/PSU/S2/PSU_2015_42sh/src
**
** Made by sebastien vidal
** Login   <vidal_s@epitech.net>
**
** Started on  Tue Oct 18 15:23:43 2016 sebastien vidal
** Last update Wed Oct 19 15:34:28 2016 Matteo
*/

#include <stdlib.h>
#include "shell.h"

static int	list_size(t_env *data)
{
  int		i;
  i = 0;
  while (data != NULL)
    {
      i = i + 1;
      data = data->next;
    }
  return (i);
}

char		**list_to_tab(t_env *data)
{
  int		i;
  int		count;
  char		**tab;

  count = 0;
  if ((i = list_size(data)) == 0)
    return (NULL);
  if (!(tab = calloc((i + 1), sizeof(char *))))
    return (NULL);
  while (data != NULL)
    {
      tab[count] = data->env_line;
      count = count + 1;
      data = data->next;
    }
  tab[count] = NULL;
  return (tab);
}
