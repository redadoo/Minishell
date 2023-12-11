/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:21:54 by edoardo           #+#    #+#             */
/*   Updated: 2023/12/11 15:13:55 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static void	echo_util(t_token *tmp)
{
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
}

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
	echo_util(tmp);
	if (option == 0)
		write(1, "\n", 1);
}
