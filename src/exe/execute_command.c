/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:16:45 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/17 17:36:11 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static void set_fd(t_minishell *mini)
{
	t_token	*tmp;

	tmp = mini->start;
	
	if (ft_strncmp(tmp->str,"<",1) == 0)
	{
		
	}
	
	while (tmp)
	{
		tmp = tmp->next;
	}
	
}

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
			set_fd(mini);
		}
		tmp = tmp->next;
	}
}

