
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

static void init_util(t_minishell *minishell, char *tokens)
{
	t_token *tmp;

	tmp = (t_token *)malloc(sizeof(t_token));
	tmp->str = tokens;
	tmp->next = NULL;
	tmp->prev = last_element(minishell->start);
	tmp->type = 0;
	last_element(minishell->start)->next = tmp;
}

static void init_token(t_minishell *minishell, char **tokens)
{
	int     i;
	t_token *tmp;

	i = -1;
	while (tokens[++i])
	{
		if (minishell->start == NULL)
		{
			minishell->start = (t_token *)malloc(sizeof(t_token));
			minishell->start->str = tokens[i];
			minishell->start->next = NULL;
			minishell->start->prev = NULL;
			minishell->start->type = 0;
		}
		else
		{
			init_util(minishell, tokens[i]);
			// tmp = (t_token *)malloc(sizeof(t_token));
			// tmp->str = tokens[i];
			// tmp->next = NULL;
			// tmp->prev = NULL;
			// tmp->type = 0;
			// last_element(minishell->start)->next = tmp;
		}
	}
}

static void print_list(t_token *token)
{

	while(token->next)
	{
		printf("%s %d\n", token->str, token->type);
		token = token->next;
	}
	printf("%s %d\n", token->str, token->type);
}

void process_input(char *input, t_minishell *minishell)
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
	parser(minishell);
	print_list(minishell->start);
	free_token(&minishell->start);
}
