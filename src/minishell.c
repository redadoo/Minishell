/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 01:58:41 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/14 19:15:48 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_sig	g_sig;

void	free_all(t_minishell *minishell)
{
	printf("\33[0;33mlogout\33[0m\n");
	free_matrix(minishell->env);
	free_token(&minishell->start);
	free_token(&minishell->env_start);
	free(minishell);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	int			i;
	char		*input;
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	input = NULL;
	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	minishell->env_start = NULL;
	minishell->start = NULL;
	make_list(minishell, envp);
	minishell->env = init_env(envp);
	minishell->stdin = dup(0);
	minishell->stdout = dup(1);
	i = 0;
	while (true)
	{
		init_signal();
		ignore_signal_for_shell();
		input = readline(PROMPT);
		process_input(input, minishell);
		i++;
	}
	free_all(minishell);
}
