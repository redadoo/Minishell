/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_io3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:51:21 by fborroto          #+#    #+#             */
/*   Updated: 2024/03/28 12:42:19 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	check_hdc_line(char **line, t_manage_red *io, bool *res)
{
	if (*line == NULL)
	{
		ft_putendl_fd("Error \n here-document delimited by end-of-file: wanted",
			STDERR_FILENO);
		*res = true;
		return (false);
	}
	if (ft_strcmp(*line, io->hdc) == 0)
	{
		*res = true;
		return (false);
	}
	return (true);
}

static bool	fill_heredoc(t_manage_red *io, int fd)
{
	char	*line;
	bool	ret;

	ret = false;
	line = NULL;
	while (1)
	{
		signals_on();
		line = readline(">");
		signals_off();
		if (!check_hdc_line(&line, io, &ret))
			break ;
		ft_putendl_fd(line, fd);
		safe_free(line);
	}
	safe_free(line);
	return (ret);
}

static bool	get_heredoc(t_manage_red *io)
{
	int		tmp_fd;
	bool	res;

	res = true;
	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		g_exit_status = 1;
		perror(strerror(errno));
		return (false);
	}
	res = fill_heredoc(io, tmp_fd);
	close(tmp_fd);
	return (res);
}

static char	*get_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin("/tmp/.msh_hdc_", number);
	free(number);
	i++;
	return (name);
}

void	parse_heredoc(t_cmd **last, t_token **token_lst)
{
	t_token			*temp;
	t_cmd			*cmd;
	t_manage_red	*io;

	temp = *token_lst;
	cmd = last_cmd(*last);
	init_io(cmd);
	io = cmd->manage_red;
	if (!del_file(io, true))
		return ;
	io->infile = get_heredoc_name();
	io->hdc = ft_strdup(temp->next->str);
	if (get_heredoc(io))
		io->fd_in = open(io->infile, O_RDONLY);
	else
		io->fd_in = -1;
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
