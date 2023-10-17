/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:16:45 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/17 12:56:30 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	exe_command(t_minishell *mini)
{
	int		i;
	char	*str;
	t_token	*tmp;

	i = 0;
	tmp = mini->start;
	while (tmp)
	{
		if (tmp->type == CMD && builtins(mini, tmp))
		{
		}
		else
		{
		}
		tmp = tmp->next;
	}
}
