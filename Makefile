# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/20 11:58:27 by edoardo           #+#    #+#              #
#    Updated: 2024/03/27 21:14:23 by edoardo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		  	= minishell

CC			  	= gcc 
FLAGS		  	= -Wall -Wextra -Werror 
RM			  	= rm -rf

OBJDIR        	= .objFiles

BUILTINS_FILE	= src/builtins/builtins src/builtins/cd src/builtins/echo src/builtins/env_command src/builtins/exit src/builtins/export src/builtins/pwd src/builtins/unset
ENV_FILE	  	= src/env/env
EXE_FILE	  	= src/exe/execute_command src/exe/execute_utils  src/exe/execute_utils2
HELP_FILE	  	= src/help_file/environment_variables src/help_file/input src/help_file/str_utils src/help_file/token_utils src/help_file/token_utils2 src/help_file/str_utils2 src/help_file/free_utils src/help_file/free_utils2
LEXER_FILES	  	= src/lexer/lexer src/lexer/lexer_utils
PARSER_FILE   	= src/parser/parser src/parser/parser_utils src/parser/parser_utils2 src/parser/parser_commands src/parser/parse_cmd_io src/parser/parse_cmd_io2 src/parser/parse_cmd_io3 src/parser/parse_cmd_utils
SIGNAL_FILE   	= src/signals/signals src/signals/signal_utils
MAIN_FILE	  	= src/minishell

FILES		  	= $(MAIN_FILE) $(SIGNAL_FILE)  $(PARSER_FILE) $(LEXER_FILES) $(HELP_FILE) $(EXE_FILE) $(ENV_FILE) $(BUILTINS_FILE)

SRC			  	= $(FILES:=.c)
OBJ			  	= $(addprefix $(OBJDIR)/, $(FILES:=.o))
HEADER		  	= minishell.h

NONE			="\033[0m"
GREEN			="\033[32m"
GRAY			="\033[2;37m"
CURSIVE			="\033[3m"
YELLOW			="\033[1;33"

.PHONY: all clean fclean re leaks

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@echo $(CURSIVE)$(GRAY) "     - Making object files..." $(NONE)
	@echo $(CURSIVE) $(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@$(CC)  $(FLAGS) $(OBJ) $(OPTS) -o $(NAME) -Llib/libft/ -lft -lreadline
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJDIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(OPTS) -c $< -o $@

compile_and_run: re
	@./$(NAME)

run:
	@./$(NAME)

leaks: re
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file=leaks.txt ./$(NAME)

clean:
	@$(RM) $(OBJDIR) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all