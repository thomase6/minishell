# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/19 10:07:05 by texenber          #+#    #+#              #
#    Updated: 2025/12/19 15:48:44 by texenber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

#ingredients
SRC_DIR := src
OBJ_DIR := obj
INC_DIR := inc
SRCS :=	\
	main.c
SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR := libft
LIBFT_LIB := $(LIBFT_DIR)/libft.a

CC := cc
WARN := -Wall -Werror -Wextra
ifeq ($(NOWARN), 1)
	WARN :=
endif
CFLAGS := $(WARN) -I$(INC_DIR)
LDFLAGS := -L$(LIBFT_DIR)
LDLIBS := -lft -lreadline

#utensils
RM := rm -f 
LM := make -C 
MAKEFLAGS += --no-print-directory
DIR_DUP = mkdir -p $(@D)

#recipe
all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@
	$(info CREATED $(NAME))

$(LIBFT_LIB):
	$(LM) $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
	$(RM) $(OBJS)
	$(LM) $(LIBFT_DIR) clean
	$(info sweep sweep)

fclean: clean
	$(RM) $(NAME)
	$(LM) $(LIBFT_DIR) fclean
	rm -rf $(OBJ_DIR)
	$(info SWEEP SWEEP)

re:
	$(MAKE) fclean
	$(MAKE) all

#special
.PHONY: clean fclean re
.SILENT: