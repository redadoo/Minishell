/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 01:58:41 by edoardo           #+#    #+#             */
/*   Updated: 2023/11/26 21:12:04 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_sig	g_sig;

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	input = NULL;
	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	minishell->start = NULL;
	minishell->env_start = NULL;
	minishell->env = init_env(envp);
	make_list(minishell, minishell->env);
	minishell->exe = (t_ppbx *)malloc(sizeof(t_ppbx));
	rl_clear_history();
	while (true)
	{
		init_signal();
		ignore_signal_for_shell();
		input = readline(PROMPT);
		if (ft_strcmp(input,"") != 0)
		{
			add_history(input);
		}
		process_input(input, minishell);
		free(input);
		waitpid(-1, NULL, 0);
	}
	free_all(minishell);
}
