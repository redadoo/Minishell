/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:38:42 by edoardo           #+#    #+#             */
/*   Updated: 2023/09/24 20:09:13 by edoardo          ###   ########.fr       */
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
# include <termios.h>
# include <dirent.h>
# include <fcntl.h>
# include <string.h>

# define PROMPT "\033[0;35mminishell>\033[0m "

typedef struct	s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}			t_token;

typedef struct s_minishell
{
	char    **env;
	t_token *start;
}   t_minishell;


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

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		pipe[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*filein;
	char	*fileout;
	char	**cmd1;
	char	**cmd2;
	char	*cmd1_path;
	char	*cmd2_path;
}	t_pipex;


int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t 	len_matrix(char **matrix);
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

/* Pipex */

int		execute_command(t_minishell *minishell);
char	*return_path(char *cmd, char**env);
void	exe_cmd_bonus(t_ppbx pipex, int i, char**argv, char **envp);
void	exit_bonus(t_ppbx pipex, int status);
char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*acces_command(char *cmd_name, char **paths);
char	*ft_substr(char const *s, unsigned int start, unsigned int len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char *backup, char *buff);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_get_line(char *backup);
char	*get_next_line(int fd);
char	*ft_get_line(char *backup);
char	*ft_backup(char *backup);
char	*ft_strchr(const char *s, int c);
char	*ft_statstr(int fd, char *statstr);
void	close_pipes(t_ppbx pipex);
void	creat_pipes(t_ppbx pipex);
void	free_pipex(char **cmd, char *path);

t_pipex	*init_pipex(char **argv, char **envp);
void	check_args(t_pipex *p);
void	exit_program(t_pipex *p, int status);
void	execute_command(t_pipex *p, char **env);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	**ft_split(const char *s, char c);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlen_t(const char *str);
char	*ft_substr(char const *s, unsigned int start, unsigned int len);
void	*ft_calloc(size_t count, size_t size);
char	*get_next_line(int fd);
char	*ft_statstr(int fd, char *statstr);
char	*ft_strjoin(char *backup, char *buff);
char	*ft_strchr(const char *str, int ch);
char	*ft_backup(char *backup);
char	*ft_get_line(char *backup);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	first_child(t_pipex *p, char **env);
void	second_child(t_pipex *p, char **env);
char	*acces_command(char *cmd_name, char **paths);
char	*my_getenv(char *name, char **env);
void	free_command(char **tab);

/* builtins command */


void builtins(t_minishell *minishell);
void pwd();
void echo(t_minishell *mini, int index);
#endif
