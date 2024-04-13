/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:21:21 by fborroto          #+#    #+#             */
/*   Updated: 2024/03/24 15:44:59 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern long long	g_exit_status;

static int	sig_expand(char *expanded, int *index)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_itoa(g_exit_status);
	while (tmp[i])
	{
		expanded[i] = tmp[i];
		i++;
	}
	safe_free(tmp);
	*index = *index + 1;
	return (i);
}

static int	envariable_expand(char *expanded, char *str, t_token *env,
		int *index)
{
	int		i;
	char	*tmp;

	i = 0;
	if (str[i] == '?')
		return (sig_expand(expanded, index));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	*index += i;
	if (find_var_n(env, str, i))
	{
		tmp = ft_get_envar(find_var_n(env, str, i)->str);
		i = -1;
		while (tmp[++i])
			expanded[i] = tmp[i];
		free(tmp);
		return (i);
	}
	return (0);
}

static void	expanded_str(char *tmp, char *str, t_token *env)
{
	int	i;
	int	j;
	int	flag;

	j = 0;
	i = -1;
	flag = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			flag++;
		if (str[i] == '\'' && !(flag % 2))
		{
			tmp[j++] = str[i];
			while (str[++i] && str[i] != '\'')
				tmp[j++] = str[i];
			tmp[j++] = str[i];
		}
		else if (str[i] && str[i] == '$' && str[i + 1] && ((ft_isalnum(str[i
							+ 1]) || str[i + 1] == '_') || str[i + 1] == '?'))
			j += envariable_expand(&tmp[j], &str[i + 1], env, &i);
		else
			tmp[j++] = str[i];
	}
}

bool	set_envariable(t_token *token, t_token *env)
{
	char	*tmp;

	if (strchr(token->str, '$') && !(token->prev
			&& token->prev->type == HEREDOC))
	{
		if (envstr_len(token->str, env) != 0)
		{
			tmp = (char *)malloc(sizeof(char) * (envstr_len(token->str, env)
						+ 1));
			if (!tmp)
				return (false);
			tmp[envstr_len(token->str, env)] = 0;
			expanded_str(tmp, token->str, env);
			free(token->str);
			token->str = tmp;
			return (true);
		}
		return (false);
	}
	return (true);
}
