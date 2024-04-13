/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:32:19 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/27 20:00:15 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtins(t_minishell *mini, t_cmd *command)
{
	if (ft_strcmp("export", command->str) == 0)
		g_exit_status = (export(mini, command));
	else if (ft_strcmp("exit", command->str) == 0)
		ft_exit(mini, command);
	else if (ft_strcmp("env", command->str) == 0)
		g_exit_status = (env_command(mini->env_start));
	else if (ft_strcmp("pwd", command->str) == 0)
		g_exit_status = (pwd());
	else if (ft_strcmp("echo", command->str) == 0)
		g_exit_status = (echo(command));
	else if (ft_strcmp("cd", command->str) == 0)
		g_exit_status = (cd(command, mini));
	else if (ft_strcmp("unset", command->str) == 0)
		g_exit_status = (ft_unset(mini, command));
	return (g_exit_status);
}

int	is_builtin(char *str)
{
	if (ft_strcmp("export", str) == 0)
		return (0);
	else if (ft_strcmp("env", str) == 0)
		return (0);
	else if (ft_strcmp("exit", str) == 0)
		return (0);
	else if (ft_strcmp("pwd", str) == 0)
		return (0);
	else if (ft_strcmp("echo", str) == 0)
		return (0);
	else if (ft_strcmp("cd", str) == 0)
		return (0);
	else if (ft_strcmp("unset", str) == 0)
		return (0);
	else if (ft_strcmp("exit", str) == 0)
		return (0);
	return (1);
}
