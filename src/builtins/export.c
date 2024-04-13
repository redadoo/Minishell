/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:07:52 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/28 12:32:34 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	free_matrix(to_sort);
	return (sorted);
}

void	print_sorted_env(t_minishell *mini)
{
	int		i;
	char	**env_sorted;

	i = 0;
	env_sorted = NULL;
	env_sorted = token_to_matrix(mini->env_start);
	env_sorted = sort(env_sorted);
	while (env_sorted[i])
	{
		printf("%s\n", env_sorted[i]);
		i++;
	}
	free_matrix(env_sorted);
}

int	export(t_minishell *mini, t_cmd *command)
{
	int	i;

	i = 1;
	if (matrix_len(command->args) == 0)
		print_sorted_env(mini);
	else
	{
		while (command->args[i])
		{
			if (command->args[i])
			{
				change_env(mini, command->args[i]);
			}
			i++;
		}
	}
	return (g_exit_status);
}
