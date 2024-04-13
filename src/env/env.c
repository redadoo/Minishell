/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:09:17 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/17 19:17:46 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_var(t_minishell *mini, char *str)
{
	int		i;
	int		j;
	t_token	*token;

	j = 0;
	i = -1;
	token = mini->env_start;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			j = 1;
			break ;
		}
	}
	if (j == 0)
		return (2);
	while (token)
	{
		if (strncmp(token->str, str, i) == 0)
			return (1);
		token = token->next;
	}
	return (0);
}

static char	*set_shlvl(char **env, int i)
{
	char	*str;
	char	*str1;

	str = ft_itoa(ft_atoi(&env[i][6]) + 1);
	str1 = ft_strjoin("SHLVL=", str);
	free(str);
	return (str1);
}

void	env_to_list(t_minishell *minishell, char **env)
{
	int		i;
	t_token	*tmp;

	i = -1;
	while (env[++i])
	{
		if (minishell->env_start == NULL)
		{
			minishell->env_start = (t_token *)malloc(sizeof(t_token));
			minishell->env_start->str = ft_strdup(env[i]);
			minishell->env_start->next = NULL;
			minishell->env_start->prev = NULL;
			minishell->env_start->type = 0;
		}
		else
		{
			tmp = (t_token *)malloc(sizeof(t_token));
			tmp->str = ft_strdup(env[i]);
			tmp->next = NULL;
			tmp->prev = last_element(minishell->env_start);
			tmp->type = 0;
			last_element(minishell->env_start)->next = tmp;
		}
	}
}

char	**init_env(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i])
		i++;
	env = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
	{
		if (!(ft_strncmp("SHLVL=", envp[i], 6)))
			env[i] = set_shlvl(envp, i);
		else if (!(ft_strncmp("SHELL=", envp[i], 6)))
			env[i] = ft_strdup("SHELL=minishell");
		else
		{
			env[i] = ft_strdup(envp[i]);
			if (env[i])
				continue ;
			free(env[i]);
			exit(write(1, "error", 6));
		}
	}
	env[i] = 0;
	return (env);
}
