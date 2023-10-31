/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:41:40 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/31 18:29:45 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

size_t	len_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
			i++;
	}
	return (i);
}

void	print_list(t_token *token)
{
	while (token)
	{
		printf("%s, %d\n", token->str, token->type);
		token = token->next;
	}
	printf("\n");
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

void	*ft_memdele(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}