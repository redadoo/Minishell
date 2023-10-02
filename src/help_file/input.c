
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

static void init_token(t_minishell *minishell, char **tokens)
{
	int	i;
	t_token *token;
	t_token *tmp;
	t_token *first_element;

	i = 0;
	token = (t_token *)malloc(sizeof(t_token));
	token->str = tokens[i];
	//type of token function
	first_element = token;
	while (tokens[i])
	{
		tmp = (t_token *)malloc(sizeof(t_token));
		tmp->str = tokens[i];
		//type of token function
		token->next = tmp;
		tmp-> prev = token;
		token = tmp;
		i++;
	}
	token->next = first_element;
	minishell->start = first_element;
	minishell->lenght = i;
}

void process_input(char *input,t_minishell *minishell)
{
	int     i;
	char    **tokens;

	i = 0;
	if (input == NULL)
		return ;
	tokens = ft_lexer(input);
	if (!(tokens[0]))
	{
		readline(PROMPT);
		return;
	}
	init_token(minishell, tokens);
	printf("%i\n",minishell->lenght);
	free_matrix(tokens);
}
