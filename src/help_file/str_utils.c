/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:07:33 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/27 20:18:22 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

char	*add_quote(char *str)
{
	int		i;
	int		j;
	char	*val;

	j = 0;
	i = -1;
	val = (char *)malloc(sizeof(char) * ft_strlen(str) + 2);
	while (str[++i])
	{
		val[j] = str[i];
		if (str[i] == '=')
		{
			val[j + 1] = '"';
			j++;
		}
		if (str[i + 1] == '\0')
		{
			val[j + 1] = '"';
			j++;
			val[j] = '\0';
			break ;
		}
		j++;
	}
	return (val);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
