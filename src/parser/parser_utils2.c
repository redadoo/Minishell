/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:06:06 by fborroto          #+#    #+#             */
/*   Updated: 2024/03/27 20:27:04 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern long long	g_exit_status;

t_token	*find_var_n(t_token *env, char *str, int n)
{
	while (env)
	{
		if (strncmp(env->str, str, n) == 0)
		{
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}

static int	envariable_is_sig(void)
{
	int		len;
	char	*tmp;

	tmp = ft_itoa(g_exit_status);
	len = ft_strlen(tmp);
	free(tmp);
	return (len);
}

static int	envariable_len(char *str, t_token *env, int *index)
{
	int	i;

	i = 0;
	if (str[i] == '?')
	{
		*index = *index + 1;
		return (envariable_is_sig());
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	*index += i;
	if (find_var_n(env, str, i))
		return (ft_strlen(ft_get_envar(find_var_n(env, str, i)->str)));
	else
		return (0);
}

int	envstr_len(char *str, t_token *env)
{
	int	i;
	int	count;
	int	flag;

	count = 0;
	i = -1;
	flag = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			flag++;
		if (str[i] == '\'' && !(flag % 2))
		{
			while (str[++i] != '\'')
				count++;
			count += 2;
		}
		else if (str[i] && str[i] == '$' && str[i + 1] && ((ft_isalnum(str[i
							+ 1]) || str[i + 1] == '_') || str[i + 1] == '?'))
			count += envariable_len(&str[i + 1], env, &i);
		else
			count++;
	}
	return (count);
}

int	token_check(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type == PIPE)
		return (ft_putendl_fd("syntax error near unexpected token |",
				STDERR_FILENO), 1);
	while (tmp)
	{
		if (tmp->type == PIPE && !tmp->next)
			return (ft_putendl_fd("syntax error unexpected token 'newline'",
					STDERR_FILENO), 1);
		else if (is_redirect(tmp->type) == 0 && (!tmp->next || (tmp->next
					&& (tmp->next->type == EMPTY
						|| (is_redirect(tmp->next->type) == 0
							|| tmp->next->type == PIPE)))))
		{
			ft_putendl_fd("syntax error unexpected token", STDERR_FILENO);
			return (1);
		}
		else if (tmp->type == PIPE && tmp->next->type == PIPE)
			return (ft_putendl_fd("syntax error near unexpected token |",
					STDERR_FILENO), 1);
		tmp = tmp->next;
	}
	return (0);
}
