##
## Makefile for 42sh in /home/matteo/rendu/PSU_2015_42sh
## 
## Made by Matteo
## Login   <matteo@epitech.net>
## 
## Started on  Tue Oct 11 14:33:35 2016 Matteo
## Last update Fri Nov 11 13:43:29 2016 Matteo
##

DIR	= src/

GRAMMAR	= grammar/

PARSER	= parser/

UTILS	= utils/

EXEC	= execution/

ENV	= env/

BUILT	= builtins/

SRC	= $(DIR)main.c \
	  $(DIR)prompt.c \
	  $(DIR)initialisation.c \
	  $(DIR)$(ENV)list_to_tab.c \
	  $(DIR)$(ENV)get_env_line.c \
	  $(DIR)$(ENV)manip_list.c \
	  $(DIR)$(PARSER)check_other_symbols.c \
	  $(DIR)$(PARSER)check_symbols.c \
	  $(DIR)$(PARSER)command.c \
	  $(DIR)$(PARSER)parser.c \
	  $(DIR)$(PARSER)redirections.c \
	  $(DIR)$(PARSER)special_case.c \
	  $(DIR)$(PARSER)check_syntax.c \
	  $(DIR)$(PARSER)or_and_pipe.c \
	  $(DIR)$(UTILS)get_next_line.c \
	  $(DIR)$(UTILS)epur.c \
	  $(DIR)$(UTILS)str_utils.c \
	  $(DIR)$(UTILS)free_tab.c \
	  $(DIR)$(UTILS)my_getnbr.c \
	  $(DIR)$(UTILS)free_handler.c \
	  $(DIR)$(UTILS)my_str_to_wordtab.c \
	  $(DIR)$(BUILT)builtin.c \
	  $(DIR)$(BUILT)my_history.c \
	  $(DIR)$(BUILT)create_history.c \
	  $(DIR)$(BUILT)my_cd.c \
	  $(DIR)$(BUILT)my_cd_dash.c \
	  $(DIR)$(BUILT)my_echo.c \
	  $(DIR)$(BUILT)my_setenv.c \
	  $(DIR)$(BUILT)my_unsetenv.c \
	  $(DIR)$(BUILT)my_exit.c \
	  $(DIR)$(BUILT)my_alias.c \
	  $(DIR)$(BUILT)check_alias.c \
	  $(DIR)$(BUILT)print_alias.c \
	  $(DIR)$(BUILT)add_alias.c \
	  $(DIR)$(EXEC)execute_pipes.c \
	  $(DIR)$(EXEC)left_redirection.c \
	  $(DIR)$(EXEC)right_redirection.c \
	  $(DIR)$(EXEC)simple_exec.c \
	  $(DIR)$(EXEC)fd_handlers.c \
	  $(DIR)$(EXEC)path_handler.c \
	  $(DIR)$(EXEC)executions.c \

NAME	= 42sh

OBJS	= $(SRC:.c=.o)

I_DIR	= include/

CFLAGS	+= -W -Wall -Wextra -Werror -Wpadded

CFLAGS	+= -I $(I_DIR)

RM	= rm -f

CC	= gcc

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
