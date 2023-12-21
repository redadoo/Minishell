/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:41:40 by edoardo           #+#    #+#             */
/*   Updated: 2023/12/18 16:54:08 by edoardo          ###   ########.fr       */
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

void	print_list(t_token *token)
{
	while (token)
	{
		printf("%s, %d\n", token->str, token->type);
		token = token->next;
	}
	printf("\n");
}

void	free_all(t_minishell *minishell, char *str)
{
	int	status;

	if (is_num(str) == 1)
		status = 2;
	else
		status = ft_atoi(str);
	free_matrix(minishell->env);
	free_token(&minishell->start, 0);
	free_token(&minishell->env_start, 1);
	free(minishell->exe);
	free(minishell);
	exit(status);
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

int	export_bad_identifier(char *identifier)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}