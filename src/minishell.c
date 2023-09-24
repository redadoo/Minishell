/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 01:58:41 by edoardo           #+#    #+#             */
/*   Updated: 2023/09/24 17:43:39 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*path;
	char		*input;
	t_minishell	minishell;

	input = NULL;
	minishell.env = envp;
	while (1)
	{
		ignore_signal_for_shell();
		input = readline(PROMPT);
		process_input(input, &minishell);
  	}
	printf("\33[0;33mlogout\33[0m\n");
}
