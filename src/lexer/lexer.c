/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:00:51 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/05 23:26:01 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

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
