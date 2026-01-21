# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/19 10:07:05 by texenber          #+#    #+#              #
#    Updated: 2026/01/21 13:29:53 by texenber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

#ingredients

EXEC_PRE	= execution/
EXEC_SRC	= executor.c pipeline.c exec_cmd.c init_env.c builtins_dud.c /builtins/echo.c /builtins/cd.c /builtins/pwd.c /builtins/env.c /builtins/exit.c /builtins/export.c

SRC			= execution/test_main.c $(addprefix $(EXEC_PRE), $(EXEC_SRC))
SRCS		= $(addprefix $(PRE), $(SRC))
PRE			= ./src/
HEAD		= ./inc/
CC			= cc
WARN		= -Wall -Werror -Wextra
ifeq ($(NOWARN), 1)
	WARN 	=
endif
CFLAGS		= $(WARN)
LIBFT		= cd libft
ODIR		= obj/
OBJS		= $(SRCS:$(PRE)%.c=$(ODIR)%.o)

#utensils
RM			= rm -f 
LM			= make -C 
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(@D)

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