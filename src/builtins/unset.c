/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:07:00 by fborroto          #+#    #+#             */
/*   Updated: 2024/03/22 23:07:36 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(t_minishell *mini, t_cmd *command)
{
	int	i;

	i = 1;
	if (matrix_len(command->args) == 0)
		return (0);
	else
	{
		while (command->args[i])
		{
			if (command->args[i])
			{
				delete_var(mini, command->args[i]);
			}
			i++;
		}
	}
	return (0);
}
