/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:00:51 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/27 21:08:09 by edoardo          ###   ########.fr       */
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
		return (i + 1);
	}
}

char	**ft_lexer(char *str)
{
	char	**tokens;
	int		count;
	int		cstr;
	int		i;
	int		start;

	i = 0;
	start = 0;
	if (!str)
		return (NULL);
	count = ft_token_counter(str);
	while (str[start] && str[start] == ' ')
		start++;
	tokens = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	tokens[count] = NULL;
	while (i < count)
	{
		cstr = ft_token_len(str + start, ' ');
		tokens[i] = ft_substr(str, start, cstr);
		start += ft_token_start(str + start, ' ');
		i++;
	}
	return (tokens);
}
