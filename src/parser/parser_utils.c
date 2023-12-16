/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:21:21 by fborroto          #+#    #+#             */
/*   Updated: 2023/12/16 18:31:33 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int sig_exit_status;

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

static int	sig_expand(char *expanded, int *index)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_itoa(sig_exit_status); //into sig
	while (tmp[i])
	{
		expanded[i] = tmp[i];
		i++;
	}
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

void	set_envariable(t_token *token, t_token *env)
{
	char	*tmp;

	if (strchr(token->str, '$'))
	{
		tmp = (char *)malloc(sizeof(char) * (envstr_len(token->str, env) + 1));
		if (!tmp)
			return ;
		tmp[envstr_len(token->str, env)] = 0;
		expanded_str(tmp, token->str, env);
		free(token->str);
		token->str = tmp;
	}
}

//" ignora ''' " e ' ignora $$$ '