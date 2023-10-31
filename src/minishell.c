/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 01:58:41 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/31 17:43:08 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_sig		g_sig;

int	main(int argc, char **argv, char **envp)
{
	int			i;
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
	i = 0;
	while (i != 10)
	{
		init_signal();
		ignore_signal_for_shell();
		input = readline(PROMPT);
		process_input(input, minishell);
		free(input);
		i++;
	}
	free_all(minishell);
}
