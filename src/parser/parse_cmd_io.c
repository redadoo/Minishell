/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_io.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:51:21 by fborroto          #+#    #+#             */
/*   Updated: 2024/03/28 12:42:19 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	del_file(t_manage_red *io, bool infile)
{
	if (infile == true && io->infile)
	{
		if (io->fd_in == -1 || (io->outfile && io->fd_out == -1))
			return (false);
		if (io->hdc != NULL)
		{
			safe_free(io->hdc);
			io->hdc = NULL;
			unlink(io->infile);
		}
		safe_free(io->infile);
		close(io->fd_in);
	}
	else if (infile == false && io->outfile)
	{
		if (io->fd_out == -1 || (io->infile && io->fd_in == -1))
			return (false);
		safe_free(io->outfile);
		close(io->fd_out);
	}
	return (true);
}

static void	open_infile(t_manage_red *io, char *file)
{
	if (!del_file(io, true))
		return ;
	io->infile = ft_strdup(file);
	if (io->infile && io->infile[0] == '\0')
	{
		perror(strerror(errno));
		return ;
	}
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
	{
		g_exit_status = 1;
		perror(strerror(errno));
	}
}

void	init_io(t_cmd *cmd)
{
	if (!cmd->manage_red)
	{
		cmd->manage_red = malloc(sizeof * cmd->manage_red);
		if (!cmd->manage_red)
			return ;
		cmd->manage_red->outfile = NULL;
		cmd->manage_red->infile = NULL;
		cmd->manage_red->hdc = NULL;
		cmd->manage_red->fd_in = -1;
		cmd->manage_red->fd_out = -1;
		cmd->manage_red->stdin_tmp = -1;
		cmd->manage_red->stdout_tmp = -1;
	}
}

void	parse_input(t_cmd **last, t_token **token_lst)
{
	t_token	*temp;
	t_cmd	*cmd;

	temp = *token_lst;
	cmd = last_cmd(*last);
	init_io(cmd);
	open_infile(cmd->manage_red, temp->next->str);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
