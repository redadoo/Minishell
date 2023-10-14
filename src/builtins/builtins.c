/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:32:19 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/14 19:14:17 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

bool	builtins(t_minishell *minishell)
{
	if (ft_strcmp("export", minishell->start->str) == 0)
		export(minishell);
	else if (ft_strcmp("env", minishell->start->str) == 0)
		env_command(minishell->env);
	else if (ft_strcmp("exit", minishell->start->str) == 0)
		exit(1);
	else if (ft_strcmp("pwd", minishell->start->str) == 0)
		pwd();
	else if (ft_strcmp("echo", minishell->start->str) == 0)
	{
	}
	else if (ft_strcmp("cd", minishell->start->str) == 0)
	{
	}
	else if (ft_strcmp("unset", minishell->start->str) == 0)
	{
	}
	else if (minishell->start->str[0] == '$')
	{
		env_var(minishell);
	}
	else
		return (false);
	return (true);
}
