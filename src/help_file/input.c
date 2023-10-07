
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

static int check_command(t_minishell *mini)
{
	int     i;
	t_token *tmp;
	char    *list[8];

	i = 0;
	
	list[0] = "echo";
	list[1] = "cd";
	list[2] = "pwd";
	list[3] = "export";
	list[4] = "unset";
	list[5] = "env";
	list[6] = "exit";
	list[7] = NULL;
	tmp = mini->start;
	while (tmp != NULL)
	{
		while (list[i])
		{
			if (tmp->type != CMD)
				break ;
			if (ft_strcmp(tmp->str, list[i]) == 0)
			{
				printf("%s\n",list[i]);
				return (i);
			}
			i++;
		}		
		i = 0;
		tmp = tmp->next;	
	}
	
	
	return (10);
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
	char    **tokens;

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

	print_list(minishell->env_start);
	
	free_token(&minishell->start);
	free_matrix(tokens);
}
