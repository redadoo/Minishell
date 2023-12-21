/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:09:36 by edoardo           #+#    #+#             */
/*   Updated: 2023/12/21 04:21:44 by edoardo          ###   ########.fr       */
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

int len_list(t_token *token)
{
	int i;

	i = 0;
	while (token)
	{
		if (token->type == CMD)
			i++;
		token = token->next;
	}
	return (i);
}

int have_pipe(t_token *token)
{
	if (token->next)
		token = token->next;
	else 
		return (0);
	while (token)
	{
		if (token->type == CMD)
			return (0);
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

void set_null(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE)
		{
			token->type = EMPTY;
			return ;
		}
		token = token->next;
	}
}

int have_empty(t_token *token)
{
	if (token->next)
		token = token->next;
	else 
		return (0);
	while (token)
	{
		if (token->type == CMD)
			return (0);
		if (token->type == EMPTY)
			return (1);
		token = token->next;
	}
	return (0);
}
