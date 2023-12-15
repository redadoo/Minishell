/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:32:19 by edoardo           #+#    #+#             */
/*   Updated: 2023/12/15 19:17:57 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	builtins(t_minishell *mini, t_token *token)
{
	if (ft_strcmp("export", token->str) == 0)
		export(mini, token);
	else if (ft_strcmp("env", token->str) == 0 && !token->next)
		env_command(mini->env);
	else if (ft_strcmp("exit", token->str) == 0)
		exit_command(mini);
	else if (ft_strcmp("pwd", token->str) == 0)
		pwd();
	else if (ft_strcmp("echo", token->str) == 0)
		echo(&token);
	else if (ft_strcmp("cd", token->str) == 0)
		cd(token, mini->env_start);
	else if (ft_strcmp("unset", token->str) == 0)
		ft_unset(token, &mini->env_start);
	else
		return (1);
	return (0);
}

int is_builtin(char *str)
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
	else if (str[0] == '$')
		return (0);
	else
		return (1);
	return (0);
}
