/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:00:57 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/06 12:54:20 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static int	ft_sep(char *line, int i)
{
	if (line[i - 1] && line[i - 1] != '\\' && line[i] == ';')
		return (1);
	else if (line[i - 1] && line[i - 1] != '\\' && line[i] == '|')
		return (1);
	else if (line[i - 1] && line[i - 1] != '\\' && line[i] == '>' && line[i + 1]
		&& line[i + 1] == '>')
		return (2);
	else if (line[i - 1] && line[i - 1] != '\\' && line[i] == '>')
		return (1);
	return (0);
}

int	ft_quote(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'')
		{
			i++;
			if (str[i] != '\'' && str[i + 1] == 0)
				ft_error_lexer("Error: unclosed quote");
		}
		return (i);
	}
	else
	{
		i++;
		while (str[i] != '"')
		{
			i++;
			if (str[i] != '"' && str[i + 1] == 0)
				ft_error_lexer("Error: unclosed double quotes");
		}
		return (i);
	}
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

int	ft_token_start(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] == ';')
		i++;
	else if (str[i] == '|')
		i++;
	else if (str[i] == '>' && str[i + 1] && str[i + 1] == '>')
		i += 2;
	else if (str[i] == '>')
		i++;
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
	if (str[i] == ';')
		return (1);
	else if (str[i] == '|')
		return (1);
	else if (str[i] == '>' && str[i + 1] && str[i + 1] == '>')
		return (2);
	else if (str[i] == '>')
		return (1);
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
