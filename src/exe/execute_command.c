/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:16:45 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/28 12:36:35 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_folder(char *str)
{
	struct stat	path_stat;

	if (stat(str, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	execute(t_cmd *command, t_minishell *minishell)
{
	if (!command || !command->str || !check_file(command->manage_red))
		free_all(minishell);
	manage_redirect(command, minishell);
	free_matrix(minishell->env);
	minishell->env = token_to_matrix(minishell->env_start);
	if (is_path(command->str))
	{
		if (is_folder(command->str))
			return (print_error("Is a directory"));
		execve(command->str, command->args, minishell->env);
	}
	else if (is_builtin(command->str) == 1)
	{
		command->path = return_path(command->str, minishell->env);
		execve(command->path, command->args, minishell->env);
	}
	else
	{
		builtins(minishell, command);
		return (free_all(minishell));
	}
	print_error(command->str);
	g_exit_status = 127;
	free_all(minishell);
}

int	wait_commands( void )
{
	pid_t	wpid;
	int		status;

	wpid = 0;
	status = 0;
	while (wpid != -1)
		wpid = waitpid(-1, &status, 0);
	return (parse_signal(status));
}

void	manage_command(t_minishell *minishell, pid_t last_pid)
{
	t_cmd	*tmp;

	tmp = minishell->cmd;
	init_pipe(minishell);
	while (last_pid != 0 && tmp)
	{
		last_pid = fork();
		if (last_pid == 0)
			execute(tmp, minishell);
		else if (last_pid == -1)
			print_error("fork error");
		tmp = tmp->next;
	}
	close_fds(minishell->cmd, false);
	g_exit_status = wait_commands();
}

void	exe_command(t_minishell *minishell)
{
	t_cmd	*tmp;
	pid_t	last_pid;

	last_pid = -1;
	tmp = minishell->cmd;
	if (tmp != NULL && tmp->str != NULL && !tmp->next
		&& is_builtin(tmp->str) == 0)
	{
		io_redirecter(tmp->manage_red);
		close_fds(minishell->cmd, false);
		builtins(minishell, tmp);
		io_restorer(tmp->manage_red);
	}
	else if (tmp)
		manage_command(minishell, last_pid);
}
