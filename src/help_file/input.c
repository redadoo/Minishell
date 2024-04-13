/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:04:38 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/27 20:28:49 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	process_input(char *input, t_minishell *minishell)
{
	char	**tokens;

	if (input == NULL)
		return (false);
	tokens = ft_lexer(minishell, input);
	if (!(tokens[0]))
	{
		free_matrix(tokens);
		return (false);
	}
	add_history(input);
	init_tokens(&minishell->start, tokens);
	free_matrix(tokens);
	if (parser(minishell) == false)
	{
		free_token(&minishell->start);
		return (false);
	}
	exe_command(minishell);
	free_token(&minishell->start);
	return (true);
}

void	print_error(char *error)
{
	ft_putstr_fd("minishell : ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
