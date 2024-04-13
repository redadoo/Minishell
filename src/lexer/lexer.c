/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:00:51 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/27 20:10:07 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_error_lexer(t_minishell *mini, char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	ft_exit(mini, NULL);
}

int	ft_quote(t_minishell *mini, char *str)
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
				ft_error_lexer(mini, "Error: unclosed quote");
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
				ft_error_lexer(mini, "Error: unclosed double quotes");
		}
		return (i);
	}
}

char	**ft_lexer(t_minishell *mini, char *str)
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
	count = ft_token_counter(mini, str);
	while (str[start] && str[start] == ' ')
		start++;
	tokens = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	tokens[count] = NULL;
	while (i < count)
	{
		cstr = ft_token_len(mini, str + start, ' ');
		tokens[i] = ft_substr(str, start, cstr);
		start += ft_token_start(mini, str + start, ' ');
		i++;
	}
	return (tokens);
}
