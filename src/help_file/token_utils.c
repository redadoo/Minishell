/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:09:36 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/30 16:08:53 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

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

void	free_token(t_token **token, int flag)
{
	t_token	*tmp;

	tmp = (*token);
	while ((*token))
	{
		tmp = (*token);
		(*token) = (*token)->next;
		if (flag == 1)
			free(tmp->str);
		free(tmp);
	}
	free((*token));
}

t_token	*return_cmd(t_token *token, int index)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == CMD && count == index)
		{
			return (token);
		}
		if (token->type == CMD)
			count++;
		token = token->next;
	}
	return (token);
}
