/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:00:57 by edoardo           #+#    #+#             */
/*   Updated: 2023/09/18 17:00:57 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	ft_error_lexer(char *str)
{
	printf("%s\n", str);
	exit(0);
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
		else
		{
			count++;
			if (str[i] == '"' || str[i] == '\'')
			{
				i += ft_quote(str + i);
			}
			while (str[i] && str[i] != ' ')
				i++;
		}
	}
	return (count);
}

int	ft_token_start(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i += ft_quote(str + i);
		}
		i++;
	}
	while (str[i] && str[i] == c)
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i += ft_quote(str + i);
		}
		i++;
	}
	return (i);
}

int	ft_token_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i += ft_quote(str + i);
		}
		i++;
	}
	return (i);
}
