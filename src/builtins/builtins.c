/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:32:19 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/31 17:48:59 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

bool	builtins(t_minishell *mini, t_token *token)
{
	extern t_sig	g_sig;

	if (ft_strcmp("export", token->str) == 0)
		export(mini, token);
	else if (ft_strcmp("env", token->str) == 0)
		env_command(mini->env);
	else if (ft_strcmp("exit", token->str) == 0)
		exit_command(mini);
	else if (ft_strcmp("pwd", token->str) == 0)
		pwd();
	else if (ft_strcmp("echo", token->str) == 0)
		echo(&token);
	else if (ft_strcmp("cd", token->str) == 0)
	{
		printf("ciao\n");
		cd(token, mini->env_start);
	}
	else if (ft_strcmp("unset", token->str) == 0)
		ft_unset(token, &mini->env_start);
	else if (token->str[0] == '$')
		env_var(mini);
	else
		return (false);
	g_sig.exit_status = 0;
	return (true);
}
