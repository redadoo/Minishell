/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:07:00 by fborroto          #+#    #+#             */
/*   Updated: 2023/10/30 09:23:29 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static void	ft_memdel(void *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

static void	free_node(t_token **env_start, t_token *env)
{
	t_token	*tmp;

	tmp = env;
	if ((*env_start) == env && env->next == NULL)
	{
		ft_memdel(env->str);
		env->str = NULL;
		env->next = NULL;
		return ;
	}
	if ((*env_start) == tmp)
	{
		(*env_start) = env->next;
		ft_memdel(env->str);
		env->str = NULL;
		env->next = NULL;
		return ;
	}
	ft_memdel(env->str);
	ft_memdel(env);
}

static void	setvar(t_token *token, t_token **env)
{
	t_token	*tmp;
	t_token	*tmp1;

	tmp = NULL;
	if (find_var((*env), token->str)->next)
	{
		tmp = find_var((*env), token->str)->next;
		if (find_var((*env), token->str)->prev)
		{
			tmp1 = find_var((*env), token->str)->prev;
			find_var((*env), token->str)->next->prev = tmp1;
		}
	}
	if (find_var((*env), token->str)->prev)
		find_var((*env), token->str)->prev->next = tmp;
}

int	ft_unset(t_token *token, t_token **env)
{
	t_token	*start;
	t_token	*tmp;

	start = (*env);
	if (!(token->next))
		return (0);
	token = token->next;
	while (token && token->type == ARG)
	{
		(*env) = start;
		tmp = NULL;
		if (find_var((*env), token->str))
		{
			tmp = find_var((*env), token->str);
			setvar(token, env);
			free_node(&start, tmp);
		}
		token = token->next;
	}
	(*env) = start;
	return (0);
}
