/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:50:54 by fborroto          #+#    #+#             */
/*   Updated: 2024/03/27 19:57:28 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	type_arg(t_token *token)
{
	if (ft_strcmp(token->str, ">") == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<<") == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(token->str, "<") == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, "\0") == 0)
		token->type = EMPTY;
	else if (token->prev == NULL || token->prev->type == PIPE)
		token->type = CMD;
	else if (token->prev->prev && is_redirect(token->prev->prev->type) == 0
		&& (token->prev->prev->prev == NULL
			|| token->prev->prev->prev->type == PIPE))
	{
		token->type = CMD;
	}
	else
		token->type = ARG;
}

static int	quote_count(char *str)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			check++;
			while (str[i] != '\'')
				i++;
		}
		else if (str[i] == '"')
		{
			i++;
			check++;
			while (str[i] != '"')
				i++;
		}
		i++;
	}
	return (i - (check * 2) + 1);
}

static char	*new_str(char *tmp, char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				tmp[j++] = str[i];
		}
		else if (str[i] == '"')
		{
			while (str[++i] != '"')
				tmp[j++] = str[i];
		}
		else
			tmp[j++] = str[i];
	}
	tmp[quote_count(str) - 1] = 0;
	free(str);
	return (tmp);
}

static void	remove_quotes(t_token *token)
{
	char	*tmp;

	if ((strchr(token->str, '\'') || strchr(token->str, '"')))
	{
		tmp = (char *)malloc(sizeof(char) * quote_count(token->str));
		if (!tmp)
			return ;
		token->str = new_str(tmp, token->str);
	}
}

bool	parser(t_minishell *minishell)
{
	t_token	*token;
	t_token	*tmp;

	token = minishell->start;
	while (token)
	{
		if (set_envariable(token, minishell->env_start))
		{
			type_arg(token);
			remove_quotes(token);
			token = token->next;
		}
		else
		{
			tmp = token->next;
			delete_token(&minishell->start, token);
			token = tmp;
		}
	}
	if (minishell->start == NULL)
		return (false);
	if (token_check(minishell->start))
		return (false);
	command_handler(minishell, minishell->start);
	return (true);
}
