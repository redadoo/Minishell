/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:00:57 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/23 20:07:58 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static int	ft_sep(char *line, int i)
{
	if (i == 0)
		return (0);
	else if (line[i] == '|')
		return (1);
	else if (line[i] == '>' && line[i + 1] && line[i + 1] == '>')
		return (2);
	else if (line[i] == '<' && line[i + 1] && line[i + 1] == '<')
		return (2);
	else if (line[i] == '>')
		return (1);
	else if (line[i] == '<')
		return (1);
	return (0);
}

int	ft_token_counter(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else if (ft_sep(str, i))
		{
			i += ft_sep(str, i);
			count++;
		}
		else
		{
			count++;
			if (str[i] == '"' || str[i] == '\'')
				i += ft_quote(str + i);
			while (str[i] && str[i] != ' ' && !(ft_sep(str, i)))
				i++;
		}
	}
	return (count);
}

static int	ft_redirection(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
		return (2);
	else if (str[i] == '|')
		return (1);
	else if (str[i] == '>' && str[i + 1] && str[i + 1] == '>')
		return (2);
	else if (str[i] == '>')
		return (1);
	else if (str[i] == '<')
		return (1);
	return (0);
}

int	ft_token_start(char *str, char c)
{
	int	i;

	i = 0;
	if (ft_redirection(str))
		i += (ft_redirection(str));
	else
	{
		while (str[i] && str[i] != c && !(ft_sep(str, i)))
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				i += ft_quote(str + i);
			}
			i++;
		}
	}
	while (str[i] && str[i] == c)
		i++;
	return (i);
}

int	ft_token_len(char *str, char c)
{
	int	i;

	i = 0;
	if (ft_redirection(str))
		return (ft_redirection(str));
	while (str[i] && str[i] != c && !(ft_sep(str, i)))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i += ft_quote(str + i);
		}
		i++;
	}
	return (i);
}
