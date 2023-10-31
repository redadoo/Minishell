/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:33:25 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/31 16:35:34 by edoardo          ###   ########.fr       */
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

static char	**parse_cmd_util(int arg, int count, t_token *tmp)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * (arg + 1));
	count = 0;
	while (count < arg)
	{
		tab[count] = ft_strdup(tmp->str);
		count++;
		tmp = tmp->next;
	}
	tab[arg] = NULL;
	return (tab);
}

char	**parse_cmd(t_token *token, int n)
{
	int		arg;
	int		count;
	t_token	*tmp;

	arg = 1;
	count = 0;
	tmp = token;
	while (token)
	{
		if (token->type == CMD && count == n)
		{
			tmp = token;
			token = token->next;
			while (token && token->type == ARG)
			{
				arg++;
				token = token->next;
			}
			return (parse_cmd_util(arg, count, tmp));
		}
		if (token->type == CMD)
			count++;
		token = token->next;
	}
	return (NULL);
}
