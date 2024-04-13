/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:00:57 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/27 20:26:37 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_sep(char *line, int i)
{
	if (line[i] == '|')
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

int	ft_token_counter(t_minishell *mini, char *str)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while (str[i[0]])
	{
		if (str[i[0]] == ' ')
			i[0]++;
		else if (ft_sep(str, i[0]))
		{
			i[0] += ft_sep(str, i[0]);
			i[1]++;
		}
		else
		{
			i[1]++;
			while (str[i[0]] && str[i[0]] != ' ' && !(ft_sep(str, i[0])))
			{
				if (str[i[0]] == '"' || str[i[0]] == '\'')
					i[0] += ft_quote(mini, str + i[0]);
				i[0]++;
			}
		}
	}
	return (i[1]);
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

int	ft_token_start(t_minishell *mini, char *str, char c)
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
				i += ft_quote(mini, str + i);
			}
			i++;
		}
	}
	while (str[i] && str[i] == c)
		i++;
	return (i);
}

int	ft_token_len(t_minishell *mini, char *str, char c)
{
	int	i;

	i = 0;
	if (ft_redirection(str))
		return (ft_redirection(str));
	while (str[i] && str[i] != c && !(ft_sep(str, i)))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i += ft_quote(mini, str + i);
		}
		i++;
	}
	return (i);
}
