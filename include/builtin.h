/*
** builtin.h for n4s in /home/gayrau_a/rendu_tek1/S2/PSU/PSU_2015_42sh/include
**
** Made by gayrau_a
** Login   <gayrau_a@epitech.net>
**
** Started on  Thu Oct 20 16:03:57 2016 gayrau_a
** Last update Mon Oct 24 22:28:57 2016 Matteo
*/

#ifndef BUILTIN_H_
# define BUILTIN_H_

#include "shell.h"

# define NEWLINE "-n"
# define ENV_VAR '$'
# define RET '?'
# define ECHO "echo"
# define CD "cd"
# define SETENV "setenv"
# define UNSETENV "unsetenv"
# define ENV "env"
# define EXIT "exit"
# define ECHO "echo"
# define HIST "history"
# define ALIAS "alias"

typedef struct		s_builtin
{
  char			*arg;
  int			(*fct)(char **, t_shell *);
}			t_builtin;

int			exec_builtin(char **, t_shell *);
int			check_builtin(char *);

/*
** Builtins utils
*/

int			my_cd_dash(t_shell *);
int			change_pwd(t_shell *);

/*
** Builtins
*/

int			my_cd(char **, t_shell *);
int			my_echo(char **, t_shell *);
int			my_history(char **, t_shell *);
int			my_exit(char **, t_shell *);
int			my_env(char **, t_shell *);
int			my_setenv(char **, t_shell *);
int			my_unsetenv(char **, t_shell *);
int			my_alias(char **, t_shell *);

static const t_builtin	g_builtin[]=
  {
    {ECHO, &my_echo},
    {CD, &my_cd},
    {ENV, &my_env},
    {SETENV, &my_setenv},
    {UNSETENV, &my_unsetenv},
    {EXIT, &my_exit},
    {HIST, &my_history},
    {ALIAS, &my_alias},
    {NULL, NULL}
  };

#endif /* !BUILTIN_H_ */
