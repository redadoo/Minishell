/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:10:01 by fborroto          #+#    #+#             */
/*   Updated: 2024/03/22 16:54:03 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	cmd_args_nb(t_token *token)
{
	t_token	*tmp;
	int		i;

	tmp = token;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == ARG)
			i++;
		else if (is_redirect(tmp->type) == 0)
		{
			if (tmp->next->next)
				token = tmp->next;
			else
				break ;
		}
		tmp = tmp->next;
	}
	return (i);
}

static void	get_cmd_args(t_cmd *cmd, t_token *token_start)
{
	t_token	*token;
	int		size;
	int		i;

	token = token_start;
	i = 1;
	size = cmd_args_nb(token);
	cmd->args = malloc(sizeof(char *) * (size + 2));
	if (!cmd->args)
		return ;
	cmd->args[0] = ft_strdup(cmd->str);
	cmd->args[size + 1] = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type == ARG)
			cmd->args[i++] = ft_strdup(token->str);
		else if (is_redirect(token->type) == 0)
		{
			if (token->next->next)
				token = token->next;
			else
				break ;
		}
		token = token->next;
	}
}

static void	prep_args(t_minishell *mini, t_token *token)
{
	t_token	*tmp;
	t_cmd	*cmd;

	tmp = token;
	cmd = mini->cmd;
	while (cmd && cmd->str && tmp)
	{
		if (tmp->type == CMD)
		{
			if (tmp->next)
			{
				tmp = tmp->next;
				get_cmd_args(cmd, tmp);
			}
			cmd = cmd->next;
		}
		tmp = tmp->next;
	}
}

static void	prep_cmds(t_minishell *mini, t_token *token)
{
	t_cmd	*cmd;

	if (!mini || !mini->cmd)
		return ;
	cmd = mini->cmd;
	if (token->next)
		prep_args(mini, mini->start);
	while (cmd && cmd->str)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof * cmd->args * 2);
			cmd->args[0] = ft_strdup(cmd->str);
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
	cmd = last_cmd(mini->cmd);
}

void	command_handler(t_minishell *mini, t_token *token)
{
	t_token	*temp;

	temp = token;
	if (strcmp(temp->str, "\0") == 0)
		return ;
	while (temp)
	{
		if (temp == token)
			cmd_adder(&mini->cmd, cmd_creator());
		if (temp->type == CMD || temp->type == ARG)
			parse_word(&mini->cmd, &temp);
		else if (temp->type == INPUT)
			parse_input(&mini->cmd, &temp);
		else if (temp->type == TRUNC)
			parse_trunc(&mini->cmd, &temp);
		else if (temp->type == HEREDOC)
			parse_heredoc(&mini->cmd, &temp);
		else if (temp->type == APPEND)
			parse_append(&mini->cmd, &temp);
		else if (temp->type == PIPE)
			parse_pipe(&mini->cmd, &temp);
		else if (!temp)
			break ;
	}
	prep_cmds(mini, mini->start);
}
