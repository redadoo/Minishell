/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:05:58 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/31 15:11:35 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"
#include <string.h>

int	is_in_env(t_token *env_start, char *name)
{
	while (env_start)
	{
		if (strncmp(env_start->str, name, len_var_name(name)))
			return (1);
		env_start = env_start->next;
	}
	return (0);
}

int	len_var_name(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

char	*print_var(char *str)
{
	int		i;
	int		j;
	int		count;
	char	*new_str;

	i = -1;
	j = 0;
	count = 0;
	while (str[++i])
	{
		if (j != 0)
			count++;
		if (str[i] == '=')
			j = 1;
	}
	new_str = (char *)malloc(sizeof(char) * count);
	i = i - count;
	j = -1;
	while (str[i])
	{
		new_str[++j] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	env_var(t_minishell *mini)
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
		if (strncmp(mini->env[i], var, ft_strlen(var)) == 0)
		{
			print_var(mini->env[i]);
			break ;
		}
	}
}

char	*ft_get_envar(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (str[i] != '=')
		i++;
	j = i;
	while (str[j])
		j++;
	new_str = (char *)malloc(sizeof(char) * (j - i + 1));
	j = 0;
	while (str[i++])
	{
		new_str[j] = str[i];
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}
