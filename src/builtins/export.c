/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:07:52 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/29 17:50:21 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static void	change_env(t_minishell *mini, char *str)
{
	t_token	*tmp;

	tmp = find_var(mini->env_start, str);
	if (tmp == NULL)
		return ;
	free(tmp->str);
	tmp->str = (add_quote(str));
}

static int	count_arg(t_token *token)
{
	int	i;

	i = 0;
	token = token->next;
	while (token)
	{
		if (token->type == CMD || token->type == PIPE)
			return (i);
		else if (token->type == ARG)
			i++;
		token = token->next;
	}
	return (i);
}

char	**sort(char **to_sort)
{
	int		i;
	int		j;
	int		k;
	char	**sorted;

	i = 0;
	while (to_sort[i])
		++i;
	sorted = malloc(sizeof(char *) * (i + 1));
	sorted[i] = NULL;
	i = -1;
	while (to_sort[++i])
	{
		j = -1;
		k = 0;
		while (to_sort[++j])
			if (ft_strncmp(to_sort[i], to_sort[j], ft_strlen(to_sort[i])) > 0)
				k++;
		sorted[k] = to_sort[i];
	}
	return (sorted);
}

void	print_sorted_env(t_minishell *mini)
{
	t_token	*tmp;
	char	**sorted;

	sorted = sort(mini->env);
	tmp = mini->env_start;
	while (tmp)
	{
		printf("declare -x ");
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
	free(sorted);
}

void	export(t_minishell *mini, t_token *token)
{
	if (count_arg(token) == 0)
		print_sorted_env(mini);
	else
	{
		token = token->next;
		while (token)
		{
			if (check_var(mini, token->str) == 2)
				add_to_env(&mini->env_start, token->str, 2);
			else if (check_var(mini, token->str) == 1)
				change_env(mini, token->str);
			else
			{
				add_to_env(&mini->env_start, token->str, 1);
				break ;
			}
			token = token->next;
		}
	}
}
