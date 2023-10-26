/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:16:45 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/26 16:37:15 by edoardo          ###   ########.fr       */
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
	set_exe(mini);
	
/* 	printf("%s\n",mini->exe->filein);
	printf("%s\n",mini->exe->fileout); */
	
	
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
	find_infile(mini);
	find_outfile(mini);
}



