/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:38:42 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/31 17:46:22 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define PROMPT "\033[0;35mminishell>\033[0m "

typedef enum TYPE
{
	EMPTY = 0,
	STOP = 1,
	TRUNC = 2,
	APPEND = 3,
	INPUT = 4,
	PIPE = 5,
	CMD = 6,
	ARG = 7
}					t_type;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_ppbx
{
	int				in_fd;
	int				out_fd;
	int				cmd_number;
	pid_t			pid;
	int				*pipe;
	char			*filein;
	char			*fileout;
	char			**cmd;
	char			*cmd_path;
}					t_ppbx;

typedef struct s_minishell
{
	int				std_in;
	int				std_out;
	int				lenght;
	char			**env;
	char			*pipe;
	t_token			*env_start;
	t_token			*start;
	t_ppbx			*exe;
}					t_minishell;

typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}					t_sig;

/* utils */
void				free_matrix(char **matrix);
size_t				len_matrix(char **matrix);
void				print_list(t_token *token);
void				free_all(t_minishell *minishell);
void				*ft_memdele(void *ptr);

/* token utils */
t_token				*last_element(t_token *token);
char				**token_to_matrix(t_token *token);
t_token				*find_var(t_token *token, char *str);
void				free_token(t_token **token, int flag);
t_token				*return_cmd(t_token *token, int index);

/* str utils */
char				*add_quote(char *str);
int					ft_strcmp(const char *s1, const char *s2);

/* env var */
int					len_var_name(char *str);
char				*print_var(char *str);
void				env_var(t_minishell *mini);
int					is_in_env(t_token *env_start, char *name);

/* input */
void				process_input(char *input, t_minishell *minishell);

/* signal */
void				init_signal(void);
void				inthandler(int sig);
void				ignore_signal_for_shell(void);

/* parser */
void				parser(t_minishell *minishell);
void				set_envariable(t_token *token, t_token *env);

/* lexer */
char				**ft_lexer(char *str);
int					ft_quote(char *str);
void				ft_error_lexer(char *str);
int					ft_token_counter(char *str);
int					ft_token_start(char *str, char c);
int					ft_token_len(char *str, char c);

/* env */
int					check_var(t_minishell *mini, char *str);
void				make_list(t_minishell *minishell, char **env);
void				add_to_env(t_token **env, char *str, int flag);
char				**init_env(char **envp);
char				*ft_get_envar(char *str);

/* builtins */
bool				builtins(t_minishell *mini, t_token *token);

/* echo */
void				echo(t_token **token);

/* exit */
void				exit_command(t_minishell *mini);

/* env_command */
void				env_command(char **mini);

/* export */
char				**sort(char **to_sort);
void				print_sorted_env(t_minishell *mini);
void				export(t_minishell *mini, t_token *token);

/* pwd */
void				pwd(void);

/* unset */
int					ft_unset(t_token *token, t_token **env);

/* cd */
int	cd(t_token *tokens, t_token *env);

/* execute command */
char				*return_path(char *cmd, char **env);
void				exe_command(t_minishell *mini);
void				find_infile(t_minishell *mini);
void				find_outfile(t_minishell *mini);
char				*acces_command(char *cmd_name, char **paths);
void				set_exe(t_minishell *mini);
void				check_arg(t_minishell *mini);
void				close_pipes(t_ppbx *pipex);
int					sub_dup2(int i, t_ppbx *p);
int					count_cmd(t_token *token);
void				exe_cmd(t_minishell *mini, int i);
char				**parse_cmd(t_token *token, int n);
char				**token_to_matrix(t_token *token);
#endif
