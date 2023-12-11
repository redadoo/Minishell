/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:21:54 by edoardo           #+#    #+#             */
/*   Updated: 2023/12/11 15:04:25 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	echo(t_token **token)
{
	t_token	*tmp;
	int		option;

	option = 0;
	tmp = (*token)->next;
	if (tmp && ft_strcmp(tmp->str, "-n") == 0)
	{
		option = 1;
		tmp = tmp->next;
	}
	while (tmp && (tmp->type == ARG || tmp->type == STOP))
	{
		if (tmp->type == STOP)
		{
			if (tmp->next->next)
				tmp = tmp->next->next;
			else
				break ;
		}
		if (tmp->str)
			ft_putstr_fd(tmp->str, 1);
		if (tmp->next && tmp->next->str != NULL)
			write(1, " ", 1);
		tmp = tmp->next;
	}
	if (option == 0)
		write(1, "\n", 1);
}
