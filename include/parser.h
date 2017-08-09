/*
** parser.h for 42sh in /home/matteo/rendu/test/parseur
**
** Made by Matteo
** Login   <matteo@epitech.net>
**
** Started on  Wed Oct 19 11:56:13 2016 Matteo
** Last update Fri Nov 11 13:44:47 2016 Matteo
*/

#ifndef PARSER_H_
# define PARSER_H_

/*
** Symbols
*/

# define R_LEFT "<"
# define R_RIGHT ">"
# define DR_LEFT "<<"
# define DR_RIGHT ">>"
# define PIPE "|"
# define AND "&&"
# define OR "||"
# define SEMICOLON ";"

/*
** Status maccros
*/

# define SUCCESS 0
# define FAILURE 1

/*
** Type of the node
*/

typedef enum		s_type
  {
    CMD = 1,
    T_FILE,
    T_PIPE,
    RIGHT,
    LEFT,
    D_RIGHT,
    D_LEFT,
    T_AND,
    T_OR,
    UNKNOWN
  }			t_type;

/*
** Structure to build tree
*/

typedef struct		s_node
{
  t_type		type;
  int			fd_in;
  int			fd_out;
  int			cmd_len;
  char			*path;
  char			**args;
  char			**address_tmp;
  struct s_node		*left;
  struct s_node		*right;
}			t_node;

typedef struct		s_token
{
  int			i;
  int			padding;
  char			**tab;
}			t_token;

t_node			*create_node();
int			check_syntax(char *);

/*
** Redirections handlers
*/

int			redir_exp(t_node **, t_token *);
int			redir_left_norm(t_node **, t_token *);
int			redir_left_spe(t_node **, t_token *);
int			redir_right(t_node **, t_token *);
int			redir_right_norm(t_node **, t_token *);
int			redir_right_spe(t_node **, t_token *);

/*
** Misc expression handler
*/

int			expression(t_node **, t_token *);
int			or_exp(t_node **, t_token *);
int			and_exp(t_node **, t_token *);
int			pipe_exp(t_node **, t_token *);
int			expression(t_node **, t_token *);
int			command_exp(t_node **, t_token *);
int			cmd_exp(t_token *);
int			file_exp(t_node **, t_token *);

/*
** Symbols checking
*/

int			is_left_redir(char *);
int			is_right_redir(char *);
int			is_pipe(char *);
int			is_and_or_or_bin(char *);
int			special_case(t_node **, t_token *);
int			is_redir_or_sep(char *);

#endif /* !PARSER_H_ */
