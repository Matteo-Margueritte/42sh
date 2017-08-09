/*
** utils.h for 42sh in /home/matteo/rendu/PSU_2015_42sh/include
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Tue Oct 11 14:38:53 2016 Matteo
** Last update Mon Oct 24 22:47:43 2016 Matteo
*/

#ifndef UTILS_H_
# define UTILS_H_

#include "shell.h"

void			my_putstr(char *);
int			my_getnbr(char *);
char			**my_str_to_wordtab(char *, char);
char			**list_to_tab(t_env *);
char			*get_env_line(char *);
char			*cut_str(char *str, const int);
char			*epur(char *str);

/*
** Free handlers
*/

void			free_tab(char **);
void			free_alias(t_alias *);
void			free_tree(t_node *);
void			free_env(t_env *);

#endif /* !UTILS_H_ */
