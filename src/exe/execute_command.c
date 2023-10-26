/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:16:45 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/26 18:03:43 by edoardo          ###   ########.fr       */
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

	
}

void set_exe(t_minishell *mini)
{
	find_infile(mini);
	find_outfile(mini);
}

static int foo(char *str)
{
	
}

