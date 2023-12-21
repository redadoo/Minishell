/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:32:19 by edoardo           #+#    #+#             */
/*   Updated: 2023/12/19 23:26:38 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

extern long long sig_exit_status;

int	builtins(t_minishell *mini, t_token *token)
{
	if (ft_strcmp("export", token->str) == 0)
		return(export(mini, token));
	else if (ft_strcmp("exit", token->str) == 0)
		ft_exit(mini);
	else if (ft_strcmp("env", token->str) == 0)
		return(env_command(mini->env));
	else if (ft_strcmp("pwd", token->str) == 0)
		return(pwd());
	else if (ft_strcmp("echo", token->str) == 0)
		return(echo(&token));
	else if (ft_strcmp("cd", token->str) == 0)
		return(cd(token, mini->env_start));
	else if (ft_strcmp("unset", token->str) == 0)
		return(ft_unset(token, &mini->env_start));
	return (3);
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
	else if (ft_strcmp("exit", str) == 0)
		return (0);
	return (1);
}
