/*
** str_utils.c for 42sh in /home/matteo/rendu/PSU_2015_42sh/src/utils
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Sun Oct 23 14:11:19 2016 Matteo
** Last update Sun Oct 23 16:17:53 2016 Matteo
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void		my_putstr(char *str)
{
  if (str != NULL)
    write(0, str, strlen(str));
}

char		*cut_str(char *str, const int len)
{
  char		*new_str;

  if (str == NULL ||
      ((new_str = malloc(sizeof(char) * (strlen(str) + 1))) == NULL))
    return (NULL);
  new_str = strcpy(new_str, str);
  new_str[len] = '\0';
  return (new_str);
}
