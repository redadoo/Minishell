
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:35:39 by edoardo           #+#    #+#             */
/*   Updated: 2023/09/24 16:23:49 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static int return_lenght(char **tokens)
{
	int		i;
	int		j;
	size_t count;

	i = 0;
	j = 0;
	count = 0;
	while (tokens[i])
	{
		while (tokens[i][j])
		{
			if (tokens[i][j] == '|')
				count++;
			j++;
		}
		i++;
		j = 0;
	}
	return (count + 1);
}

static bool check_command(t_minishell *mini)
{
	int     i;
	int		j;
	char    *list[8];

	i = 0;
	j = 0;
	list[0] = "echo";
	list[1] = "cd";
	list[2] = "cd";
	list[3] = "pwd";
	list[4] = "export";    
	list[5] = "unset";
	list[6] = "env";
	list[7] = "exit";	
	return (false);
}

void process_input(char *input,t_minishell *minishell)
{
	int     i;
	char    **tokens;

	i = 0;
	if (input == NULL)
		return ;
	tokens = ft_lexer(input);
	init_token(minishell, tokens);
	free_tab(tokens);
	if (!(minishell->tokens[0]))
	{
		readline(PROMPT);
		return;
	}
}