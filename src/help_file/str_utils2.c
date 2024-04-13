/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:32:11 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/20 18:21:57 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_redirect(int n)
{
	if (n == HEREDOC || n == APPEND || n == INPUT || n == TRUNC)
		return (0);
	return (1);
}

void	export_bad_identifier(char *identifier)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

bool	is_path(char *cmd)
{
	if (ft_strchr(cmd, '/') == NULL)
		return (false);
	return (true);
}

int	matrix_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		i++;
	}
	return (i - 1);
}
