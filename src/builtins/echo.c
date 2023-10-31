/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:21:54 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/31 14:46:25 by fborroto         ###   ########.fr       */
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
	while (tmp && tmp->type == ARG)
	{
		if (tmp->str)
			ft_putstr_fd(tmp->str, 1);
		if (tmp->next && tmp->next->str != NULL)
			write(1, " ", 1);
		tmp = tmp->next;
	}
	if (option == 0)
		write(1, "\n", 1);
}
