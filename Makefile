# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 01:55:20 by edoardo           #+#    #+#              #
#    Updated: 2023/10/29 17:44:24 by edoardo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = $(MAIN_SRC) $(LIBFT_SRC) $(LEXER_SRC) $(SIGNALS_SRC) $(PIPEX_SRC) $(BUILTINS_SRC) $(HELP_SRC) $(ENV_SRC) $(PARSER_SRC) $(EXE_SRC)

MAIN_SRC = src/*.c

LIBFT_SRC = ft_libft/*.c

ENV_SRC = src/env/*.c

LEXER_SRC = src/lexer/*.c

PARSER_SRC = src/parser/*.c

SIGNALS_SRC = src/signals/*.c

BUILTINS_SRC = src/builtins/*.c

HELP_SRC = src/help_file/*.c

EXE_SRC = src/exe/*.c

OBJ = *.o

CC = gcc

CFLAGS = -lreadline -Wall -Wextra -Werror

RM = rm -rf

NONE="\033[0m"
GREEN="\033[32m"
GRAY="\033[2;37m"
CURSIVE="\033[3m"

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(CURSIVE) $(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@gcc $(OBJ) -o $(NAME) $(CFLAGS)
	@echo $(GREEN)"- Compiled -"$(NONE)
	@rm -rf $(OBJ)
	
$(OBJ): $(SRCS)
	@echo $(CURSIVE)$(GRAY) "     - Making object files..." $(NONE)
	@gcc -c $(SRCS) $(CFLAGS)

exe: all
	@echo "     - Executing $(NAME)..."
	@./$(NAME) 
	@echo "     - Done -"

leaks: all
	@echo "     - Executing $(NAME) with leaks command..."
	@valgrind --log-file="leak.txt" --leak-check=full --show-leak-kinds=all ./$(NAME)
	@echo "     - Done -"

leaks1: all
	@echo "     - Executing $(NAME) with leaks command..."
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)
	@echo "     - Done -"

norm:
	@norminette $(SRCS) lib/minishell.h
	
clean: 
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}
re: fclean all