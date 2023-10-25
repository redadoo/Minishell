/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:16:45 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/25 22:56:22 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../lib/minishell.h"

static void	set_fd(t_minishell *mini)
{
	t_token	*tmp;

	tmp = mini->start;
	if (ft_strncmp(tmp->str, "<", 1) == 0)
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
	set_exe(mini);
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

void set_exe(t_minishell *mini)
{
	mini->exe->in_fd  = find_infile(mini);
	mini->exe->out_fd = find_outfile(mini);
}



