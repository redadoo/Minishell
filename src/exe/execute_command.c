/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:16:45 by edoardo           #+#    #+#             */
/*   Updated: 2023/12/23 15:09:49 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"


static void	left_side(t_minishell *minishell, int pdes[2], t_token *token)
{
	close(STDOUT_FILENO);
	dup(pdes[1]);
	close(pdes[0]);
	close(pdes[1]);
	exe(minishell, token);
	
}

static void	right_side(t_minishell *minishell, int pdes[2], t_token *token)
{
	close(STDIN_FILENO);
	dup(pdes[0]);
	close(pdes[0]);
	close(pdes[1]);
	token = token->next;
	while (token && token->type != CMD)
		token = token->next;
	exe(minishell, token);
}

static void	exec_executables(t_minishell *minishell, t_token *token)
{
	if (builtins(minishell,token) != 3)
		return ;
	minishell->exe->cmd = parse_cmd(token);
	minishell->exe->cmd_path = return_path(minishell->exe->cmd[0], token_to_matrix(minishell->env_start));
	execve(minishell->exe->cmd_path, minishell->exe->cmd, token_to_matrix(minishell->env_start));
	sig_exit_status = 127;
	printf("%s: command not found\n", token->str);
	exit(sig_exit_status);
}

static void exe_pipe(t_minishell * minishell, t_token *token)
{
	int		temp_status;
	int		pipedes[2];
	pid_t	cpid;

	set_null(token);
	if (pipe(pipedes) == -1)
		free_all(minishell,"1");
	cpid = fork();
	if (cpid == -1)
		free_all(minishell,"1");
	if (cpid == 0)
		left_side(minishell,pipedes,token);
	right_side(minishell,pipedes,token);
	close(pipedes[0]);
	close(pipedes[1]);
	waitpid(cpid, &temp_status, 0);
	sig_exit_status = temp_status >> 8;
}

static void exe_red(t_minishell *minishell, t_token *token)
{
	t_token *tmp;
	t_token *command;

	(void)command;
	tmp = start_pars_red(minishell, token);
	command = NULL;
	printf("%s\n",tmp->str);
	while (tmp)
	{
		if (tmp->type == PIPE)
			break;
		if (tmp->type == EMPTY)
			break;
		if (tmp->type == CMD)
			command = tmp;
		if (tmp->type == TRUNC)
			redirect_output(minishell,tmp);
		if (tmp->type == APPEND)
			redirect_output(minishell,tmp);
		if (tmp->type == STOP)
			redirect_input(minishell,tmp);
		if (tmp->type == INPUT)
			redirect_input(minishell,tmp);
		tmp = tmp->next;
	}
	if (command != NULL)
		printf("pazzo");
	/* exe(minishell,command); */
	/* print_list(command); */
}

void exe(t_minishell *minishell, t_token * token)
{
	signal(SIGINT, child_signals);
	if (have_pipe(token) == 1)
		exe_pipe(minishell,token);
	else if(have_red(minishell,token) != 0)
	{
		exe_red(minishell, token);
	}
	else
		exec_executables(minishell, token);
	exit(sig_exit_status);
}

void exe_command(t_minishell *minishell)
{
	int tmp;
	int status;

	if (len_list(minishell->start) == 1)
	{
		minishell->exe->cmd = parse_cmd(minishell->start);
		minishell->exe->cmd_path = return_path(minishell->exe->cmd[0], token_to_matrix(minishell->env_start));
		tmp = builtins(minishell,return_cmd(minishell->start, 0));
		if(tmp == 3 && fork() == 0)
		{
			signal(SIGINT, child_signals);
			execve(minishell->exe->cmd_path, minishell->exe->cmd, token_to_matrix(minishell->env_start));
			sig_exit_status = 127;
			printf("%s: command not found\n", minishell->start->str);
			exit(sig_exit_status);
		}
		else if(tmp != 3)
			sig_exit_status = tmp;
		else
			sig_exit_status = 127;
	}
	else if(fork() == 0)
		exe(minishell, minishell->start);
	waitpid(-1, &status, 0);
	if (!WTERMSIG(status))
		sig_exit_status = status >> 8;
}
