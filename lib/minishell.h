/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:38:42 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/25 22:49:27 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_libft/libft.h"
# include <dirent.h>
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

# define PROMPT "\033[0;35m  minishell>\033[0m "

typedef enum TYPE
{
	EMPTY = 0,
	CMD = 1,
	ARG = 2,
	TRUNC = 3,
	APPEND = 4,
	INPUT = 5,
	PIPE = 6,
	END = 7
}					t_type;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_minishell
{
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

typedef struct s_ppbx
{
	int		in_fd;
	int		out_fd;
	int		cmd_number;
	pid_t	pid;
	int		*pipe;
	char	*filein;
	char	*fileout;
	char	**cmd;
	char	*cmd_path;
}	t_ppbx;

int					check_var(t_minishell *mini, char *str);
size_t				len_matrix(char **matrix);
void				free_matrix(char **matrix);
void				free_token(t_token **token, int flag);
t_token				*last_element(t_token *token);
char				**init_env(char **env);
void				inthandler(int sig);
void				init_signal(void);
void				make_list(t_minishell *minishell, char **env);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				ignore_signal_for_shell(void);
void				process_input(char *input, t_minishell *minishell);
char				**ft_lexer(char *str);
void				ft_error_lexer(char *str);
int					ft_quote(char *str);
int					ft_token_counter(char *str);
int					ft_token_start(char *str, char c);
int					ft_token_len(char *str, char c);
void				parser(t_minishell *minishell);
char				*return_path(char *cmd, char **env);
char				**ft_split(const char *s, char c);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
char				*acces_command(char *cmd_name, char **paths);
char				*ft_substr(char const *s, unsigned int start,
						unsigned int len);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strjoin(char *backup, char *buff);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_get_line(char *backup);
char				*get_next_line(int fd);
char				*ft_get_line(char *backup);
char				*ft_backup(char *backup);
char				*ft_strchr(const char *s, int c);
char				*ft_statstr(int fd, char *statstr);
void				free_pipex(char **cmd, char *path);
int					execute_command(t_minishell *minishell);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
char				**ft_split(const char *s, char c);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlen_t(const char *str);
char				*ft_substr(char const *s, unsigned int start,
						unsigned int len);
void				*ft_calloc(size_t count, size_t size);
char				*get_next_line(int fd);
char				*ft_statstr(int fd, char *statstr);
char				*ft_strjoin(char *backup, char *buff);
char				*ft_strchr(const char *str, int ch);
char				*ft_backup(char *backup);
char				*ft_get_line(char *backup);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*acces_command(char *cmd_name, char **paths);
char				*my_getenv(char *name, char **env);
void				free_command(char **tab);
int					ft_strcmp(const char *s1, const char *s2);
void				env_command(char **mini);
bool				builtins(t_minishell *mini, t_token *token);
void				pwd(void);
void				echo(t_minishell *mini, int index);
void				export(t_minishell *mini, t_token *token);
void				env_var(t_minishell *mini);
int					len_var_name(char *str);
int					is_in_env(t_token *env_start, char *name);
char				*add_quote(char *str);
t_token				*find_var(t_token *token, char *str);
void				add_to_env(t_token **env, char *str, int flag);


/* EXECUTE COMMAND */

void				exe_command(t_minishell *mini);
int					find_infile(t_minishell *mini);
int					find_outfile(t_minishell *mini);
char				*return_path(char *cmd, char **env);
char				*acces_command(char *cmd_name, char **paths);
void				set_exe(t_minishell *mini);

#endif
