/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:28:38 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/31 17:42:41 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	sub_dup2(int i, t_ppbx *p)
{
	if (p->cmd_number == 1)
	{
		if (dup2(p->in_fd, STDIN_FILENO) == -1)
		{
			return (-1);
		}
		if (dup2(p->out_fd, STDOUT_FILENO) == -1)
		{
			return (-1);
		}
	}
	else if (i == 0)
	{
		if (dup2(p->in_fd, STDIN_FILENO) == -1)
		{
			return (-1);
		}
		if (dup2(p->pipe[2 * i + 1], STDOUT_FILENO) == -1)
		{
			return (-1);
		}
	}
	else if (i == p->cmd_number - 1)
	{
		if (dup2(p->pipe[2 * i - 2], STDIN_FILENO) == -1)
		{
			return (-1);
		}
		if (dup2(p->out_fd, STDOUT_FILENO) == -1)
		{	
			return (-1);
		}
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
