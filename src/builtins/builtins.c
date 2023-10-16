/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:32:19 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/16 14:20:45 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

bool	builtins(t_minishell *mini,t_token *token)
{
	if (ft_strcmp("export", token->str) == 0)
		export(mini, token);
	else if (ft_strcmp("env", token->str) == 0)
		env_command(mini->env);
	else if (ft_strcmp("exit", token->str) == 0)
		exit(1);
	else if (ft_strcmp("pwd", token->str) == 0)
		pwd();
	else if (ft_strcmp("echo", token->str) == 0)
	{
		
	}
	else if (ft_strcmp("cd", token->str) == 0)
	{
	}
	else if (ft_strcmp("unset", token->str) == 0)
	{
	}
	else if (token->str[0] == '$')
	{
		env_var(mini);
	}
	else
		return (false);
	return (true);
}
