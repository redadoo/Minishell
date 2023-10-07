/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 01:58:41 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/06 19:16:57 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int			i;
	char		*input;
	t_sig		g_sig;
	t_minishell	*minishell;


	i = 0;
	while (envp[i])
	{
		printf("%s\n",envp[i]);
		i++;
	}
	
/* 	(void)argc;
	(void)argv;
	input = NULL;
	
	minishell = (t_minishell *)malloc(sizeof(t_minishell));

	minishell->env_start = NULL;
	minishell->start = NULL;
	
	make_env(minishell, envp);
	minishell->stdin = dup(0);
	minishell->stdout = dup(1);

	i = 0;
	while (i != 4)
	{
		init_signal(g_sig);
		ignore_signal_for_shell();
		input = readline(PROMPT);
		process_input(input, minishell);
		i++;
  	}
	printf("\33[0;33mlogout\33[0m\n");
	free_token(&minishell->env_start);
	free_token(&minishell->start);
	free(minishell); */
	exit(0);
}
	
	//TODO:
	//1) Built-in Function : echo with option -n, cd with only a relative or absolute path, pwd, export, unset, env , exit
	//3) Handle environment variables
	//4) Handle $?
	//5) Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.(signals)

