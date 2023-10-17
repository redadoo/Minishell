/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:07:00 by fborroto          #+#    #+#             */
/*   Updated: 2023/10/17 18:29:51 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static size_t	env_size(t_token *env)
{
	size_t	i;

	i = 0;
	while (env->str[i] != '=')
		i++;
	return (i);
}

static void	ft_memdel(void *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

static void	free_node(t_token *env_start, t_token *env)
{
	t_token	*tmp;

	tmp = env;
	if (env_start == env && env->next == NULL)
	{
		ft_memdel(env->str);
		env->str = NULL;
		env->next = NULL;
		return ;
	}
	if (env_start == tmp)
	{
		env_start = env->next;
		ft_memdel(env->str);
		env->str = NULL;
		env->next = NULL;
		return ;
	}
	ft_memdel(env->str);
	ft_memdel(env);
}

int	ft_unset(t_token *token, t_token **env)
{
	t_token	*tmp;
	t_token	*start;

	start = (*env);
	if (!(token->next))
		return (0);
	token = token->next;
	while (token && token->type == 2)
	{
		free_node(start, find_var((*env),token->str)->str);
/* 		while ((*env))
		{
			if ((*env) && strncmp(token->str, (*env)->str,
					env_size((*env))) == 0)
			{
				tmp = (*env)->next;
				free_node(start, (*env));
				(*env) = tmp;
			}
			(*env) = (*env)->next;
		} */
		token = token->next;
	}
	(*env) = start;
}
