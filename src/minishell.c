/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 01:58:41 by edoardo           #+#    #+#             */
/*   Updated: 2023/12/13 17:05:17 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_sig	g_sig;

static void init_minishell(t_minishell *minishell, char **envp)
{
	minishell->s_exit = 0;
	minishell->start = NULL;
	minishell->env_start = NULL;
	minishell->env = init_env(envp);
	minishell->exe = (t_ppbx *)malloc(sizeof(t_ppbx));
	env_to_list(minishell, minishell->env);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	init_minishell(minishell, envp);
	rl_clear_history();
	init_signal();
	while (true)
	{
		input = readline(PROMPT);
		if (input == NULL)
			free_all(minishell);
		if (ft_strcmp(input,"") == 0)
			continue ;
		add_history(input);
		process_input(input, minishell);
		free(input);
		waitpid(-1, NULL, 0);
	}
	free_all(minishell);
}
