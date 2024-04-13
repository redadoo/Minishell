/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:48:36 by fborroto          #+#    #+#             */
/*   Updated: 2024/03/20 13:25:35 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*cmd_creator(void)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(new_node))
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_cmd));
	new_node->pipe_output = false;
	new_node->str = NULL;
	new_node->path = NULL;
	new_node->args = NULL;
	new_node->pipe_fd = 0;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	cmd_adder(t_cmd **cmdlst, t_cmd *new_node)
{
	t_cmd	*start;

	start = *cmdlst;
	if (start == NULL)
	{
		*cmdlst = new_node;
		return ;
	}
	if (cmdlst && *cmdlst && new_node)
	{
		while (start->next)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}

t_cmd	*last_cmd(t_cmd *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

void	parse_word(t_cmd **cmd, t_token **token_lst)
{
	t_token	*temp;
	t_cmd	*last;

	temp = *token_lst;
	while (temp && (temp->type == CMD || temp->type == ARG))
	{
		last = last_cmd(*cmd);
		if (temp->type == CMD)
		{
			last->str = ft_strdup(temp->str);
			temp = temp->next;
		}
		else
		{
			if (temp->type == ARG)
				temp = temp->next;
		}
	}
	*token_lst = temp;
}

void	parse_pipe(t_cmd **cmd, t_token **token_lst)
{
	t_cmd	*last;

	last = last_cmd(*cmd);
	last->pipe_output = true;
	cmd_adder(&last, cmd_creator());
	*token_lst = (*token_lst)->next;
}
