/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 23:18:52 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/24 16:04:34 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_tokens(t_token **list, char **tokens)
{
	int		i;
	t_token	*prev_node;
	t_token	*new_node;

	prev_node = NULL;
	*list = NULL;
	i = 0;
	while (tokens[i])
	{
		new_node = (t_token *)malloc(sizeof(t_token));
		new_node->str = ft_strdup(tokens[i]);
		new_node->type = 0;
		new_node->next = NULL;
		new_node->prev = prev_node;
		if (*list == NULL)
			*list = new_node;
		else
			prev_node->next = new_node;
		prev_node = new_node;
		i++;
	}
}
