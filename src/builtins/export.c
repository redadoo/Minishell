/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:07:52 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/14 19:13:00 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

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
	char	**sorted;
	int		i;

	sorted = sort(mini->env);
	i = -1;
	while (sorted[++i])
	{
		printf("declare -x ");
		printf("%s\n", sorted[i]);
	}
	free(sorted);
}

void	export(t_minishell *mini)
{
	int				i;
	extern t_sig	g_sig;

	i = 1;
	mini->pipe = ft_strdup("");
	if (i == 1)
		print_sorted_env(mini);
	g_sig.exit_status = 0;
}
