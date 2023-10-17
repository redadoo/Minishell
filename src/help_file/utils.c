/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:41:40 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/17 12:47:16 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	free_token(t_token **token)
{
	t_token	*tmp;

	tmp = (*token);
	while ((*token))
	{
		tmp = (*token);
		(*token) = (*token)->next;
		free(tmp);
	}
	free((*token));
}

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

void	print_token(t_token *token)
{
	while (token)
	{
		printf("%s\n", token->str);
		token = token->next;
	}
}

t_token	*last_element(t_token *token)
{
	while (token->next)
	{
		token = token->next;
	}
	return (token);
}

t_token	*find_var(t_token *token, char *str)
{
	while (token)
	{
		if (strncmp(token->str, str, len_var_name(str)) == 0 && len_var_name(str) == len_var_name(token->str))
		{
			printf("dagospia\n");
			return (token);
		}
		token = token->next;
	}
	return (NULL);
}