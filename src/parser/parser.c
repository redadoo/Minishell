/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:50:54 by fborroto          #+#    #+#             */
/*   Updated: 2023/10/25 23:01:38 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void	type_arg(t_token *token)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<<") == 0)
		token->type = STOP;
	else if (ft_strcmp(token->str, "<") == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0)
		token->type = PIPE;
	else if (token->prev == NULL || token->prev->type == PIPE
		|| (token->prev->prev && token->prev->prev->type <= INPUT))
		token->type = CMD;
	else
		token->type = ARG;
}

void	parser(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->start;
	while (token)
	{
		type_arg(token);
		token = token->next;
	}
}
