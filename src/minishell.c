/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 01:58:41 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/27 19:43:15 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	g_exit_status = 0;

static void	init_minishell(t_minishell *minishell, char **envp)
{
	minishell->start = NULL;
	minishell->env_start = NULL;
	minishell->env = init_env(envp);
	init_tokens(&minishell->env_start, minishell->env);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	init_minishell(minishell, envp);
	while (true)
	{
		signals_on();
		input = readline(PROMPT);
		signals_off();
		if (input == NULL)
			ft_exit(minishell, NULL);
		if (ft_strcmp(input, "") == 0)
			continue ;
		if (process_input(input, minishell) == false)
			g_exit_status = 2;
		free_cmd(minishell);
		safe_free(input);
	}
	clear_history();
	free_all(minishell);
}
