/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:25:06 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/28 12:36:35 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	safe_free(void *_ptr)
{
	if (_ptr != NULL)
	{
		free(_ptr);
		_ptr = NULL;
	}
}

void	free_cmd(t_minishell *mini)
{
	t_cmd	*tmp;

	while (mini->cmd)
	{
		tmp = mini->cmd;
		mini->cmd = mini->cmd->next;
		free_io(tmp->manage_red);
		safe_free(tmp->path);
		safe_free(tmp->str);
		safe_free(tmp->pipe_fd);
		free_matrix(tmp->args);
		safe_free(tmp);
	}
	safe_free(mini->cmd);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		safe_free(matrix[i]);
		i++;
	}
	safe_free(matrix);
}

void	free_all(t_minishell *minishell)
{
	close_fds(minishell->cmd, true);
	free_cmd(minishell);
	free_matrix(minishell->env);
	free_token(&minishell->start);
	free_token(&minishell->env_start);
	free(minishell);
	exit(g_exit_status);
}

void	free_token(t_token **token)
{
	t_token	*tmp;

	if (token == NULL)
		return ;
	tmp = (*token);
	while ((*token))
	{
		tmp = (*token);
		(*token) = (*token)->next;
		safe_free(tmp->str);
		safe_free(tmp);
	}
	safe_free((*token));
}
