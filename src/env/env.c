/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:09:17 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/03 16:27:35 by edoardo          ###   ########.fr       */
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
			minishell->env_start->str = env[i];
			minishell->env_start->next = NULL;
			minishell->env_start->prev = NULL;
			minishell->env_start->type = 0;
		}
		else
		{
			tmp = (t_token *)malloc(sizeof(t_token));
			tmp->str = env[i];
			tmp->next = NULL;
			tmp->prev = NULL;
			tmp->type = 0;
			last_element(minishell->env_start)->next = tmp;
		}
	}
}
