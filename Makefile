# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 01:55:20 by edoardo           #+#    #+#              #
#    Updated: 2023/09/18 17:56:43 by edoardo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = $(MAIN_SRC) $(LIBFT_SRC) $(LEXER_SRC) $(SIGNALS_SRC)

MAIN_SRC = src/*.c

LIBFT_SRC = ft_libft/*.c

LEXER_SRC = src/lexer/*.c

SIGNALS_SRC = src/signals/*.c

OBJ = *.o

CC = gcc

CFLAGS = -lreadline

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
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)
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