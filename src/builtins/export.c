/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:07:52 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/14 16:10:41 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static char	*ft_charjoin(char *s1, char s2)
{
	size_t	i;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1)
		return (NULL);
	str = malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	str[i++] = s2;
	str[ft_strlen(s1) + 1] = '\0';
	free(s1);
	return (str);
}

static void	ft_strappend(char **dst, char *to_append)
{
	int	i;

	i = -1;
	while (to_append[++i])
		*dst = ft_charjoin(*dst, to_append[i]);
}

static void	ft_envappend(char **dst, char *to_append)
{
	int	i;
	int	appended;

	i = -1;
	appended = 0;
	while (to_append[++i])
	{
		*dst = ft_charjoin(*dst, to_append[i]);
		if (to_append[i] == '=' && !appended)
		{
			appended = 1;
			*dst = ft_charjoin(*dst, '\"');
		}
	}
	*dst = ft_charjoin(*dst, '\"');
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
	char	**sorted;
	int		i;

	sorted = sort(mini->env);
	i = -1;
	while (sorted[++i])
	{
		printf("declare -x ");
		printf("%s\n",sorted[i]);
	}
	free(sorted);
}

void export(t_minishell *mini)
{
	int	i;
	extern t_sig	g_sig;

	i = 1;
	mini->pipe = ft_strdup("");
	if (i == 1)
		print_sorted_env(mini);
	g_sig.exit_status = 0;
}