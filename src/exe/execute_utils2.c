/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:28:38 by edoardo           #+#    #+#             */
/*   Updated: 2023/12/19 16:10:40 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	redirect_input_until(char *del)
{
	char	*buff;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		buff = readline("> ");
		if (ft_strcmp(del, buff) == 0)
			break ;
		ft_putendl_fd(buff, fd[1]);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(buff);
}

int	sub_dup2(int i, t_ppbx *p)
{
	if (p->cmd_number == 1)
	{
		if (dup2(p->in_fd, STDIN_FILENO) == -1)
			return (-1);
		if (dup2(p->out_fd, STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (i == 0)
	{
		if (dup2(p->in_fd, STDIN_FILENO) == -1)
			return (-1);
		if (dup2(p->pipe[2 * i + 1], STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (i == p->cmd_number - 1)
	{
		if (dup2(p->pipe[2 * i - 2], STDIN_FILENO) == -1)
			return (-1);
		if (dup2(p->out_fd, STDOUT_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (dup2(p->pipe[2 * i - 2], STDIN_FILENO) == -1)
			return (-1);
		if (dup2(p->pipe[2 * i + 1], STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}
