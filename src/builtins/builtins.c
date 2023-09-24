/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:32:19 by edoardo           #+#    #+#             */
/*   Updated: 2023/09/24 19:45:50 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void builtins(t_minishell *minishell)
{
	if (ft_strncmp(minishell->tokens[0], "pwd",3) == 0)
		pwd();
	else if(ft_strncmp(minishell->tokens[0], "echo",4) == 0)
		echo(minishell,1);
}
