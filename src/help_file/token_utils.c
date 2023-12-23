/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:09:36 by edoardo           #+#    #+#             */
/*   Updated: 2023/12/23 14:45:23 by edoardo          ###   ########.fr       */
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

int have_red(t_minishell *minishell,t_token *token)
{
	t_token	*tmp;

	printf(" para %s\n",token->str);
	tmp = minishell->start;
	if (token != tmp)
	{
		while (tmp->next->next && (tmp->next != token))
			tmp = tmp->next;
	}
	while (tmp)
	{
		printf("%s\n",tmp->str);

		if (tmp->type == PIPE || !tmp->next)
		{
			printf("aaasaasddasnasdoasdndsoinoidnoindoiasd\n");
			return (0);
		}
		if (tmp->type == TRUNC)
			return (1);
		if (tmp->type == APPEND)
			return (2);
		if (tmp->type == STOP)
			return (3);
		if (tmp->type == INPUT)
			return (4);
		tmp = tmp->next;
	}
	printf("homis\n");
	return (0);
}


t_token *start_pars_red(t_minishell *minishell,t_token *token)
{
	t_token	*tmp;

	tmp = minishell->start;
	(void)token;
	while ((tmp) && (tmp->type != EMPTY || tmp->type != EMPTY))
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == EMPTY)
			return (tmp->next);
		if (tmp->type == PIPE)
			return (tmp->next);
		if (tmp->type == TRUNC)
			return (tmp);
		if (tmp->type == APPEND)
			return (tmp);
		if (tmp->type == STOP)
			return (tmp);
		if (tmp->type == INPUT)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
