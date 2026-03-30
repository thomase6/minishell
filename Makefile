# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/19 10:07:05 by texenber          #+#    #+#              #
#    Updated: 2026/03/29 09:22:33 by texenber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

#ingredients

LAP_PRE		= lap/
LAP_SRC		= 	lexer.c				\
          		lexer_helper.c		\
          		lexer_helper1.c		\
          		parser.c			\
          		parser_helper.c		\
          		parser_helper1.c	\
          		parser_helper2.c		\
          		cleanup.c			\
          		helper_functions.c	\
          		helper_functions1.c	\
          		helper_functions2.c 

EXEC_PRE	= execution/
EXEC_SRC	=	executor.c			\
				pipeline.c			\
				exec_cmd.c			\
				init_env.c			\
				builtins_dud.c		\
				builtins/echo.c		\
				builtins/cd.c		\
				builtins/pwd.c		\
				builtins/env.c		\
				builtins/exit.c		\
				builtins/export.c	\
				builtins/export2.c	\
				builtins/unset.c	\
				signals_in_main.c	\
				signals_in_exec.c

#execution/test_main.c
SRC			=	main.c									\
				$(addprefix $(EXEC_PRE), $(EXEC_SRC))	\
				$(addprefix $(LAP_PRE), $(LAP_SRC))
SRCS		= 	$(addprefix $(PRE), $(SRC))
PRE			= 	./src/
HEAD		= 	./inc/
CC			= 	cc
WARN		= 	-Wall -Werror -Wextra
ifeq ($(NOWARN), 1)
	WARN 	=
endif
CFLAGS		= 	$(WARN)
LIBFT		= 	cd libft
ODIR		= 	obj/
OBJS		= 	$(SRCS:$(PRE)%.c=$(ODIR)%.o)

#utensils
RM			= 	rm -f 
LM			= 	make -C 
MAKEFLAGS	+= 	--no-print-directory
DIR_DUP		= 	mkdir -p $(@D)

#recipe
all:		$(NAME)

$(ODIR)%.o: $(PRE)%.c
			$(DIR_DUP)		
			$(CC) $(CFLAGS) -c -I $(HEAD) $< -o $@

$(NAME):	$(OBJS)
			(${LIBFT} && make all)
			$(CC) $(CFLAGS) -I $(HEAD) $(OBJS) -o $(NAME) ./libft/libft.a -lreadline

clean:		
			(${LIBFT} && make clean)
			$(RM) $(OBJS)
			rm -rf $(ODIR)
			
fclean:		clean
			(${LIBFT} && make fclean)
			$(RM) $(NAME)

re:			fclean all clean

.PHONY:		all clean fclean re
