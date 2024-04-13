/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:38:42 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/28 12:42:19 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib/libft/libft.h"
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <linux/limits.h>
# define PROMPT "\033[0;35mminishell>\033[0m "

typedef enum TYPE
{
	EMPTY = 0,
	APPEND = 3,
	PIPE = 5,
	CMD = 6,
	ARG = 7,
	HEREDOC = 8,
	INPUT = 9,
	TRUNC = 10,
}					t_type;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_manage_red
{
	char			*infile;
	char			*outfile;
	char			*hdc;
	int				fd_in;
	int				fd_out;
	int				stdin_tmp;
	int				stdout_tmp;
}					t_manage_red;

typedef struct s_cmd
{
	char			*str;
	char			*path;
	char			**args;
	bool			pipe_output;
	int				*pipe_fd;
	t_manage_red	*manage_red;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_minishell
{
	char			**env;
	t_token			*env_start;
	t_token			*start;
	t_cmd			*cmd;
}					t_minishell;

extern long long	g_exit_status;

/* utils */
void				free_matrix(char **matrix);
void				free_all(t_minishell *minishell);
void				free_cmd(t_minishell *minishell);
void				export_bad_identifier(char *identifier);
void				safe_free(void *_ptr);
void				print_error(char *error);
/* token utils */
t_token				*last_element(t_token *token);
char				**token_to_matrix(t_token *token);
t_token				*find_var(t_token *token, char *str);
void				free_token(t_token **token);
int					is_redirect(int n);
void				delete_token(t_token **tokens, t_token *delete_token);
/* str utils */
int					ft_strcmp(const char *s1, const char *s2);
bool				is_valid_id(char *str);
bool				streq(char *str1, char *str2);
/* env var */
int					len_var_name(char *str);
int					is_in_env(t_token *env_start, char *name);

/* input */
bool				process_input(char *input, t_minishell *minishell);

/* signal */
/* parser */
bool				parser(t_minishell *minishell);
int					envstr_len(char *str, t_token *env);
int					token_check(t_token *token);
bool				set_envariable(t_token *token, t_token *env);
void				command_handler(t_minishell *mini, t_token *token);
t_token				*find_var_n(t_token *env, char *str, int n);

bool				del_file(t_manage_red *io, bool infile);
void				parse_input(t_cmd **last, t_token **token_lst);
void				parse_append(t_cmd **last, t_token **token_lst);
void				parse_trunc(t_cmd **last, t_token **token_lst);
void				parse_heredoc(t_cmd **last, t_token **token_lst);
void				parse_pipe(t_cmd **cmd, t_token **token_lst);
void				parse_word(t_cmd **cmd, t_token **token_lst);
void				init_io(t_cmd *cmd);
void				cmd_adder(t_cmd **cmdlst, t_cmd *new_node);
t_cmd				*last_cmd(t_cmd *cmd);
t_cmd				*cmd_creator(void);

/* lexer */
char				**ft_lexer(t_minishell *mini, char *str);
int					ft_quote(t_minishell *mini, char *str);
void				ft_error_lexer(t_minishell *mini, char *str);
int					ft_token_counter(t_minishell *mini, char *str);
int					ft_token_start(t_minishell *mini, char *str, char c);
int					ft_token_len(t_minishell *mini, char *str, char c);

/* env */
int					check_var(t_minishell *mini, char *str);
void				env_to_list(t_minishell *minishell, char **env);
char				**init_env(char **envp);
char				*ft_get_envar(char *str);

/* builtins */
int					builtins(t_minishell *mini, t_cmd *cmd);
int					is_builtin(char *str);
/* echo */
int					echo(t_cmd *token);

/* exit */
void				ft_exit(t_minishell *mini, t_cmd *command);
/* env_command */
int					env_command(t_token *env);

/* export */
char				**sort(char **to_sort);
void				print_sorted_env(t_minishell *mini);
int					export(t_minishell *mini, t_cmd *command);

/* pwd */
int					pwd(void);

/* unset */
int					ft_unset(t_minishell *mini, t_cmd *command);

/* cd */
int					cd(t_cmd *commands, t_minishell *mini);

/* execute command */
char				*return_path(char *cmd, char **env);
void				exe_command(t_minishell *mini);
bool				init_pipe(t_minishell *minishell);
char				*acces_command(char *cmd_name, char **paths);
void				set_dup2(t_cmd *command);
void				close_pipe(t_cmd *cmds, t_cmd *current_command);
bool				is_path(char *cmd);
void				ignore_sigquit(void);
void				signals_on(void);
void				signals_off(void);
void				close_fds(t_cmd *cmds, bool close_backups);
int					matrix_len(char **args);
void				manage_command(t_minishell *minishell, pid_t last_pid);
bool				io_restorer(t_manage_red *io);
bool				io_redirecter(t_manage_red *io);
void				manage_redirect(t_cmd *command, t_minishell *minishell);
void				init_tokens(t_token **list, char **tokens);
void				free_io(t_manage_red *io);
void				change_env(t_minishell *mini, char *str);
void				delete_var(t_minishell *mini, char *str);
bool				check_file(t_manage_red *io);
int					parse_signal(int s);
#endif
