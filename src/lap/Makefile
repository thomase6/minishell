# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/12 12:45:22 by stbagdah          #+#    #+#              #
#    Updated: 2026/03/12 12:45:23 by stbagdah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ===================== Variables =====================
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Iinclude

# List all your source files exactly once
SRCS    = src/main.c \
          src/lexer.c \
          src/lexer_helper.c \
          src/lexer_helper1.c \
          src/parser.c \
          src/parser_helper.c \
          src/parser_helper1.c \
          src/pipe_handler.c \
          src/cleanup.c \
          src/helper_functions.c \
          src/helper_functions1.c \
          src/helper_functions2.c 

# Automatically generate object files from source files
OBJS    = $(SRCS:.c=.o)

# Name of the executable
NAME    = test_lexer

# ===================== Rules =====================
all: $(NAME)

# Link all object files into the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compile each .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean object files and executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Debug target to check OBJS
print:
	@echo $(OBJS)

# Declare phony targets
.PHONY: all clean fclean re print
