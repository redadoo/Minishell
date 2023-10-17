/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:07:33 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/17 16:44:18 by edoardo          ###   ########.fr       */
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
