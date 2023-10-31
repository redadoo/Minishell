/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:21:21 by fborroto          #+#    #+#             */
/*   Updated: 2023/10/31 14:55:16 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static t_token	*find_var_n(t_token *token, char *str, int n)
{
	while (token)
	{
		if (strncmp(token->str, str, n) == 0)
		{
			return (token);
		}
		token = token->next;
	}
	return (NULL);
}
static char	*dollar_var(char *str, t_token *env)
{
	char	*tmp2;
	int		i;
	int		j;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	j = i;
	while (str[j])
		j++;
	if (find_var_n(env, str, i))
	{
		if (str[i])
			tmp2 = ft_strjoin(ft_get_envar(find_var_n(env, str, i)->str),
					ft_substr(str, i, (j - i + 1))); //forse questo leakka
		else
			tmp2 = ft_get_envar(find_var_n(env, str, i)->str);
	}
	else if (!str[i])
		tmp2 = ft_strdup("");
	else
		tmp2 = ft_substr(str, i, (j - i + 1));
	free(str);
	return (tmp2);
}

static char	*token_expander(char **matrix)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = -1;
	tmp = NULL;
	tmp2 = NULL;
	while (matrix[++i])
	{
		if (matrix[i][0])
		{
			if (!tmp)
				tmp = ft_strdup(matrix[i]);
			else
			{
				tmp2 = ft_strdup(tmp);
				free(tmp);
				tmp = ft_strjoin(tmp2, matrix[i]);
				free(tmp2);
			}
		}
	}
	if(tmp)
		return (tmp);
	return (ft_strdup(""));
}

static void	uncheck_dollar(char *tmp)
{
	char	*str;

	str = ft_strjoin("$", tmp);
	free(tmp);
	tmp = ft_strdup(str);
	free(str);
}

void	set_envariable(t_token *token, t_token *env)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(token->str, '$');
	if (token->str[0] != '$')
		i++;
	if (token->str[0] == '$' && !(ft_isalnum(token->str[1])))
	{
		uncheck_dollar(tmp[0]);
		i++;
	}
	while (tmp[i])
	{
		if (!(ft_isalnum(tmp[i][0])))
			uncheck_dollar(tmp[i]);
		else
			tmp[i] = dollar_var(&tmp[i][0], env);
		i++;
	}
	free(token->str);
	token->str = token_expander(tmp);
	free_matrix(tmp);
	token->type = 0;
}
