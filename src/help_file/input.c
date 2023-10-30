/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:04:38 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/30 16:14:35 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static void	init_util(t_minishell *minishell, char *tokens)
{
	t_token	*tmp;

	tmp = (t_token *)malloc(sizeof(t_token));
	tmp->str = ft_strdup(tokens);
	tmp->next = NULL;
	tmp->prev = last_element(minishell->start);
	tmp->type = 0;
	last_element(minishell->start)->next = tmp;
}

static void	init_token(t_minishell *minishell, char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
	{
		if (minishell->start == NULL)
		{
			minishell->start = (t_token *)malloc(sizeof(t_token));
			minishell->start->str = ft_strdup(tokens[i]);
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

void	process_input(char *input, t_minishell *minishell)
{
	char			**tokens;

	if (input == NULL)
		return ;
	tokens = ft_lexer(input);
	if (!(tokens[0]))
	{
		free_matrix(tokens);
		return ;
	}
	init_token(minishell, tokens);
	parser(minishell);
	exe_command(minishell);
	free_token(&minishell->start, 1);
	free_matrix(tokens);
}
