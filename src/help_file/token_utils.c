/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:09:36 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/23 01:21:38 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**token_to_matrix(t_token *token)
{
	int		i;
	int		count;
	t_token	*tmp;
	char	**matrix;

	i = 0;
	count = 0;
	tmp = token;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	matrix = (char **)malloc(sizeof(char *) * (count + 1));
	while (i != count && token)
	{
		matrix[i] = ft_strdup(token->str);
		token = token->next;
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}

t_token	*last_element(t_token *token)
{
	if (token == NULL)
		return (NULL);
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
		if (strncmp(token->str, str, len_var_name(str)) == 0
			&& len_var_name(str) == len_var_name(token->str))
		{
			return (token);
		}
		token = token->next;
	}
	return (NULL);
}

static void	delete_head(t_token **head_ref, t_token *delete_node)
{
	if ((*head_ref)->next)
		*head_ref = (*head_ref)->next;
	else
	{
		safe_free(delete_node);
		*head_ref = NULL;
		return ;
	}
	(*head_ref)->prev = NULL;
	safe_free(delete_node->str);
	safe_free(delete_node);
	return ;
}

void	delete_token(t_token **head_ref, t_token *delete_node)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = *head_ref;
	if (delete_node == *head_ref)
		return (delete_head(head_ref, delete_node));
	while (tmp)
	{
		if (tmp == delete_node)
		{
			prev = tmp->prev;
			if (tmp->next)
				prev->next = tmp->next;
			else
				prev->next = NULL;
			if (prev->next)
				prev->next->prev = prev;
			safe_free(tmp->str);
			safe_free(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}
