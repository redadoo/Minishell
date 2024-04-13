/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:05:58 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/25 15:59:13 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <string.h>

int	is_in_env(t_token *env_start, char *name)
{
	t_token	*tmp;

	tmp = env_start;
	while (tmp)
	{
		if (strncmp(tmp->str, name, len_var_name(name)))
			return (1);
		tmp = tmp->next;
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

void	change_env(t_minishell *mini, char *str)
{
	t_token	*tmp;

	if (is_valid_id(str) == false)
	{
		g_exit_status = 1;
		return (export_bad_identifier(str));
	}
	tmp = find_var(mini->env_start, str);
	if (tmp)
	{
		safe_free(tmp->str);
		tmp->str = ft_strdup(str);
	}
	else
	{
		tmp = (t_token *)malloc(sizeof(t_token));
		tmp->next = NULL;
		tmp->prev = last_element((mini->env_start));
		tmp->str = ft_strdup(str);
		last_element(mini->env_start)->next = tmp;
	}
}

void	delete_var(t_minishell *mini, char *str)
{
	t_token	*tmp;

	tmp = find_var(mini->env_start, str);
	if (tmp)
		delete_token(&mini->env_start, tmp);
}
