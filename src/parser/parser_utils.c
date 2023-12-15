/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:21:21 by fborroto          #+#    #+#             */
/*   Updated: 2023/12/15 18:19:07 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

/* 
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
					ft_substr(str, i, (j - i + 1)));
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
	if (tmp)
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
} */

// QUELLE NUOVE
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

static void envariable_expand(char *expanded, char *str, t_token *env, int *index)
{
	int	i;
	char *tmp;
	
	i = 0;
	if (str[i] == '?')
	{
		tmp = ft_itoa(999);
		while(tmp[i])
		{
			expanded[i] = tmp[i];
			i ++;
		}
		*index = *index + 1;
		return ;
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	*index += i;
	if (find_var_n(env, str, i))
	{
		tmp = ft_get_envar(find_var_n(env, str, i)->str);
		i = -1;
		while(tmp[++i])
			expanded[i] = tmp[i];
		free(tmp);
	}
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
		{
			flag++;
			printf("ayo");
			tmp[j++] = str[i];

		}
		else if (str[i] == '\'' && !(flag % 2))
		{
			tmp[j++] = str[i];
			while (str[++i] != '\'')
				tmp[j++] = str[i];
		}
		else if (str[i] && str[i] == '$' && str[i + 1] && ((ft_isalnum(str[i
						+ 1]) || str[i + 1] == '_') || str[i + 1] == '?'))
						{
			envariable_expand(&tmp[j], &str[i + 1], env, &i);
						printf("ayo2");	
						}
		else
			tmp[j++] = str[i];
	}
}

void	set_envariable(t_token *token, t_token *env)
{
	char	*tmp;

	/* 	char	**tmp;
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
		token->type = 0; */
	if (strchr(token->str, '$'))
	{
		tmp = (char *)malloc(sizeof(char) * (envstr_len(token->str, env) + 1));
		if (!tmp)
			return ;
		tmp[envstr_len(token->str, env)] = 0;
		printf("test : %d \n", envstr_len(token->str, env));
		expanded_str(tmp, token->str, env);
		free(token->str);
		token->str = tmp;
		printf("la stirnga è: %s\n", token->str);
	}
}

//" ignora ''' " e ' ignora $$$ '