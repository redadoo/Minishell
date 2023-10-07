/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:09:17 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/07 18:43:06 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static char	*set_shlvl(char **env, int i)
{
	char	*str;

	str = ft_itoa(ft_atoi(&env[i][6]) + 1);
	return (ft_strjoin("SHLVL=", str));
}

void	make_list(t_minishell *minishell, char **env)
{
	int		i;
	t_token	*tmp;

	i = -1;

	while (env[++i])
	{
		if (minishell->env_start == NULL)
		{
			minishell->env_start = (t_token *)malloc(sizeof(t_token));
			minishell->env_start->str = NULL;
			minishell->env_start->next = NULL;
			minishell->env_start->prev = NULL;
			minishell->env_start->type = 0;
		}
		else
		{
			tmp = (t_token *)malloc(sizeof(t_token));
			tmp->str = NULL;
			tmp->next = NULL;
			tmp->prev = NULL;
			tmp->type = 0;
			last_element(minishell->env_start)->next = tmp;
		}
	}
}

void	init_env(t_token **list, char **envp)
{
	int		i;
	t_token	*tmp;
	char	**env;

	i = 0;
	while (envp[i])
		i++;

	env = (char **)malloc(sizeof(char *) * (i + 1));
	
	i = -1;
 	tmp = (*list);
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
	i = -1;
	while (env[++i])
	{
		printf("%s\n",env[i]);
	}
	
}
