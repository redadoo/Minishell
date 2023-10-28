/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 01:58:41 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/28 00:38:45 by edoardo          ###   ########.fr       */
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
/* 	minishell->std_in = dup(STDIN_FILENO);
	minishell->std_out =  dup(STDOUT_FILENO);
	dup2(minishell->std_out,STDOUT_FILENO);
	dup2(minishell->std_in,STDIN_FILENO); */
	minishell->env_start = NULL;
	minishell->start = NULL;
	minishell->env = init_env(envp);
	make_list(minishell, minishell->env);
	minishell->exe = (t_ppbx *)malloc(sizeof(t_ppbx));
	i = 0;
	while (i != 4)
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
