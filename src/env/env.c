/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:09:17 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/06 18:18:58 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void make_env(t_minishell *minishell,  char **env)
{
	int     i;
	t_token *tmp;

	i = -1;
	while (env[++i])
	{
		if (minishell->env_start == NULL)
		{
			minishell->env_start = (t_token *)malloc(sizeof(t_token));
			minishell->env_start->str = ft_strdup(env[0]);
			minishell->env_start->next = NULL;
			minishell->env_start->prev = NULL;
			minishell->env_start->type = 0;
			printf("%s\n",minishell->env_start->str);
		}
		else
		{
			tmp = (t_token *)malloc(sizeof(t_token));
			tmp->str = env[i];
			tmp->next = NULL;
			tmp->prev = NULL;
			tmp->type = 0;
			last_element(minishell->env_start)->next = tmp;
/* 			printf("%s\n", env[i]);
 */		}
	}
}
