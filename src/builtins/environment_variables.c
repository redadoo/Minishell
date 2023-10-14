/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:05:58 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/14 14:33:33 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"
#include <string.h>

char *print_var(char *str)
{
	int i;
	int j;
	int count;
	char *new_str;

	i = 0;
	j = 0;
	count = 0;
	while (str[i])
	{
		if (j != 0)
			count++;
		if (str[i] == '=')
			j = 1;
		i++;
	}
	new_str = (char *)malloc(sizeof(char) * count);
	i = i - count;
	j = 0;
	while (str[i])
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return new_str;
}

void env_var(t_minishell *mini)
{
	int		i;
	char	*var;
	
	i = 1;
	var = (char *)malloc(sizeof(char) * (ft_strlen(mini->start->str) - 1));
	
	while (mini->start->str[i])
	{
		var[i - 1] = mini->start->str[i];
		i++;
	}
	var[i - 1] = '\0';
	i = -1;
	while (mini->env[++i])
	{
		if (strncmp(mini->env[i],var,ft_strlen(var)) == 0)
		{
			print_var(mini->env[i]);
			break ;
		}
	}    
}
