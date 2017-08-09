/*
** shell.h for 42sh in /home/matteo/rendu/PSU_2015_42sh/include
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Tue Oct 11 14:34:57 2016 Matteo
** Last update Wed Dec 21 10:38:38 2016 Matteo
*/

#ifndef SHELL_H_
# define SHELL_H_

#include "parser.h"

# define FILE_RIGHTS 0644
# define EXEC_ERR ": Exec format error. Binary file not executable.\n"

# define MAX_HIST 500
# define HISTORY "/tmp/.history"

/*
** Output format code
*/

# define BOLD "\033[1m"

# define RED "\033[91m"
# define GREEN "\033[92m"
# define ORANGE "\033[93m"
# define BLUE "\033[94m"
# define MAGENTA "\033[95m"
# define CYAN "\033[96m"
# define RESET "\033[0m"

/*
** Default path if no env
*/

# define DEFAULT_PATH "PATH=/usr/sbin:/usr/bin:/sbin:/bin"

/*
** Structure pour les alias
*/

typedef struct		s_alias
{
  int			loop;
  int			padding;
  char			*alias;
  char			**cmd;
  struct s_alias	*prev;
  struct s_alias	*next;
}			t_alias;

/*
** Structure principale
*/

typedef struct		s_shell
{
  int			exit_status;
  int			ret;
  char			*pwd;
  char			*oldpwd;
  char			**env_tab;
  char			*hist[500];
  t_alias		*list_alias;
  t_node		**trees;
}			t_shell;

typedef struct		s_env
{
  char			*env_line;
  struct s_env		*next;
}			t_env;

t_env			*g_env;

/*
** Initialisation
*/

int			initialisation(t_shell *, char **);
t_env			*create_env(char **);
int			read_history(t_shell*);

/*
** Misc
*/

int		prompt(t_shell *);
void		print_prompt(int);
int		write_history(t_shell *);

/*
** Execution
*/

int		put_in_history(char *, t_shell *);
t_node		**parser(char *);
int		execute_it(t_node *, t_shell *);
int		main_execution(t_shell *);
int		simple_exec(t_node *, t_shell *);
char		*get_good_path(char *);
void		set_fd_out(t_node *, const int);
void		set_fd_in(t_node *, const int);
void		close_fds(t_node *);

/*
** Exec pipe and redirections
*/

int		execute_simple_pipe(t_node *, t_shell *);
int		init_first_pipe_spe(t_node *, t_shell *, int *);
int		prepare_pipes(t_node *, t_shell *);
int		spe_left(t_node *);
int		left_redirection(t_node *, t_shell *);
int		right_redirection(t_node *, t_shell *);

/*
** alias
*/

t_alias			*check_loop(t_alias *);
int			check_arg(char **);
t_alias			*check_list(t_alias *);
char			**add_cmd(char **);
char			*add_alias(char *);
t_alias			*add_to_alias(char **, t_alias *);
void			print_alias(t_shell *, char **);
int			my_alias(char **, t_shell *);

#endif /* !SHELL_H_ */
