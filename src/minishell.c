/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 01:58:41 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/17 18:21:54 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_sig		g_sig;

void	print_list(t_token *token)
{
	while (token)
	{
		printf("%s\n", token->str);
		token = token->next;
	}
}

void	free_all(t_minishell *minishell)
{
	printf("\33[0;33mlogout\33[0m\n");
	free_matrix(minishell->env);
	free_token(&minishell->start, 0);
	free_token(&minishell->env_start, 1);
	free(minishell->exe);
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
	minishell->env = init_env(envp);
	make_list(minishell, minishell->env);
	minishell->exe = (t_ppbx *)malloc(sizeof(t_ppbx));
	i = 0;
	while (i != 5)
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
