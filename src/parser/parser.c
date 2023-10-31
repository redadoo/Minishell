/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:50:54 by fborroto          #+#    #+#             */
/*   Updated: 2023/10/30 14:26:12 by fborroto         ###   ########.fr       */
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

static void	remove_quotes(t_token *token)
{
	int		i;
	int		check;
	char	*tmp;

	i = -1;
	check = 1;
	if (token->str[0] == '\"')
	{
		tmp = ft_substr(token->str, 1, ft_strlen(token->str) - 2);
		free(token->str);
		token->str = tmp;
	}
	else if (token->str[0] == '\'')
	{
		tmp = ft_substr(token->str, 1, ft_strlen(token->str) - 2);
		free(token->str);
		token->str = tmp;
		check = 0;
	}
	while (token->str[++i] && check)
	{
		if (token->str[i] == '$' && token->str[i + 1] && (ft_isalnum(token->str[i
				+ 1]) || token->str[i + 1] == '_'))
			token->type = 2;
	}
}

void	parser(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->start;
	while (token)
	{
		remove_quotes(token);
		if (token->type == 2)
			set_envariable(token, minishell->env_start);
		type_arg(token);
		token = token->next;
	}
}
