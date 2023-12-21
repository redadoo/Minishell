/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:32:07 by edoardo           #+#    #+#             */
/*   Updated: 2023/12/19 23:23:21 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	env_command(char **mini)
{
	int	i;

	i = 0;
	while (mini[i])
	{
		ft_putstr_fd(mini[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}
