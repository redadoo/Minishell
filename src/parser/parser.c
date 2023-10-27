/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:50:54 by fborroto          #+#    #+#             */
/*   Updated: 2023/10/27 20:18:39 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

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
