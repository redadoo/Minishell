/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:38:42 by edoardo           #+#    #+#             */
/*   Updated: 2023/09/18 20:06:44 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../ft_libft/libft.h"
# include "../pipex.h"
# include <termios.h>
# include <dirent.h>

# define PROMPT "\033[0;35mminishell>\033[0m "

typedef struct s_minishell
{
	char    **tokens;
}   t_minishell;

void	ignore_signal_for_shell();
void	process_input(char *input,t_minishell *minishell);
void    free_matrix(char **matrix);
int     test();
char	**ft_lexer(char *str);
void	ft_error_lexer(char *str);
int		ft_quote(char *str);
int		ft_token_counter(char *str);
int		ft_token_start(char *str, char c);
int		ft_token_len(char *str, char c);

#endif
