/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 01:58:41 by edoardo           #+#    #+#             */
/*   Updated: 2023/09/18 20:01:21 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*path;
	char		*input;
	char		cwd[256];
	t_minishell	minishell;

	input = NULL;
/* 	ft_strjoin(getcwd(cwd, sizeof(cwd)), "$")*/	
	while (1)
	{
		ignore_signal_for_shell();
		input = readline(PROMPT);
		process_input(input, &minishell);
	}
	printf("\33[0;33mlogout\33[0m\n");
}
