/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:01:35 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/28 12:36:35 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	io_restorer(t_manage_red *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	if (io->stdin_tmp != -1)
	{
		if (dup2(io->stdin_tmp, STDIN_FILENO) == -1)
			ret = false;
		close(io->stdin_tmp);
		io->stdin_tmp = -1;
	}
	if (io->stdout_tmp != -1)
	{
		if (dup2(io->stdout_tmp, STDOUT_FILENO) == -1)
			ret = false;
		close(io->stdout_tmp);
		io->stdout_tmp = -1;
	}
	return (ret);
}

void	close_fds(t_cmd *cmds, bool close_backups)
{
	if (cmds && cmds->manage_red)
	{
		if (cmds->manage_red->fd_in != -1)
			close(cmds->manage_red->fd_in);
		if (cmds->manage_red->fd_out != -1)
			close(cmds->manage_red->fd_out);
		if (close_backups)
			io_restorer(cmds->manage_red);
	}
	close_pipe(cmds, NULL);
}

bool	io_redirecter(t_manage_red *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	io->stdin_tmp = dup(STDIN_FILENO);
	if (io->stdin_tmp == -1)
		print_error("stdin");
	io->stdout_tmp = dup(STDOUT_FILENO);
	if (io->stdout_tmp == -1)
		print_error("stdout");
	if (io->fd_in != -1)
	{
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			print_error("dup2");
	}
	if (io->fd_out != -1)
	{
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			print_error("dup2");
	}
	return (ret);
}

void	manage_redirect(t_cmd *command, t_minishell *minishell)
{
	set_dup2(command);
	close_pipe(minishell->cmd, command);
	io_redirecter(command->manage_red);
	close_fds(minishell->cmd, false);
}

bool	check_file(t_manage_red *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if ((io->infile && io->fd_in == -1) || (io->outfile && io->fd_out == -1))
		return (false);
	return (true);
}
