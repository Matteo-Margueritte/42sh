/*
** my_getnbr.c for tetris in /home/matteo/rendu/PSU_2015_tetris/source/tools
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Tue Aug  2 16:13:50 2016 Matteo
** Last update Fri Oct 21 18:33:43 2016 Matteo
*/

#include <string.h>

static int	ten_pow(int j)
{
  int		i;
  int		nb;

  i = 0;
  if (j == 0)
    return (1);
  nb = 0;
  while (i != j)
    {
      if (i == 0)
	nb = 1;
      else
	nb = nb * 10;
      i++;
    }
  return (nb);
}

static int	check_nb(int start, int next)
{
  int		is_ok;

  is_ok = 2147483647;
  is_ok = is_ok - start;
  is_ok = is_ok - next;
  if (is_ok < 0)
    return (-1);
  return (0);
}

int		my_getnbr(char *str)
{
  int		i;
  int		j;
  int		nb;

  i = 0;
  nb = 0;
  j = strlen(str);
  if (str == NULL || str[0] == '\0')
    return (-1);
  while (str[i])
    {
      if (str[i] >= '0' && str[i] <= '9')
	{
	  if (check_nb(nb, ((str[i] - '0') * ten_pow(j))) != 0)
	    return (-1);
	  nb = nb + ((str[i] - '0') * ten_pow(j));
	}
      else
	return (-1);
      if (j != 0)
	j--;
      i++;
    }
  return (nb);
}
