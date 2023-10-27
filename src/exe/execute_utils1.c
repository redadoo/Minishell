/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:33:25 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/27 21:09:37 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	close_pipes(t_ppbx *pipex)
{
	int	i;

	i = 0;
	while (i < 2 * (pipex->cmd_number - 1))
	{
		close(pipex->pipe[i]);
		i++;
	}
	free(pipex->pipe);
	free(pipex->filein);
	free(pipex->fileout);
	pipex->pipe = NULL;
}

int	count_cmd(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == CMD)
			i++;
		token = token->next;
	}
	return (i);
}

int	sub_dup2(int i, t_ppbx *p)
{
	if (i == 0)
	{
		if (dup2(p->in_fd, 0) == -1)
			return (-1);
		if (dup2(p->pipe[2 * i + 1], 1) == -1)
			return (-1);
	}
	else if (i == p->cmd_number - 1)
	{
		if (dup2(p->pipe[2 * i - 2], 0) == -1)
			return (-1);
		if (dup2(p->out_fd, 1) == -1)
			return (-1);
	}
	else
	{
		if (dup2(p->pipe[2 * i - 2], 0) == -1)
			return (-1);
		if (dup2(p->pipe[2 * i + 1], 1) == -1)
			return (-1);
	}
	return (0);
}

char	**parse_cmd(t_token *token, int n)
{
	int		arg;
	int		count;
	char	**tab;
	t_token	*tmp;

	arg = 1;
	count = 0;
	tmp = token;
	while (token)
	{
		if (token->type == CMD)
			count++;
		if (token->type == CMD && count == n)
		{
			tmp = token;
			token = token->next;
			while (token && token->type == ARG)
			{
				arg++;
				token = token->next;
			}
			tab = (char **)malloc(sizeof(char *) * arg + 1);
			count = 0;
			while (count < arg)
			{
				tab[count] = ft_strdup(tmp->str);
				count++;
				tmp = tmp->next;
			}
			tab[arg] = NULL;
			break ;
		}
		token = token->next;
	}
	return (tab);
}
