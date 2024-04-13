/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:21:54 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/18 19:50:10 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	echo(t_cmd *cmd)
{
	int	i;
	int	option;
	int	n;

	n = 0;
	option = 0;
	i = 1;
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		option = 1;
		i++;
	}
	while (cmd->args[i])
	{
		if (n == 1)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(cmd->args[i], 1);
		n = 1;
		i++;
	}
	if (option == 0)
	{
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
