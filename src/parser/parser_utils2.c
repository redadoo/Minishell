/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:06:06 by fborroto          #+#    #+#             */
/*   Updated: 2023/12/16 18:31:22 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

extern int sig_exit_status;

static int	envariable_is_sig(void)
{
	int		len;
	char	*tmp;

	tmp = ft_itoa(sig_exit_status);
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
