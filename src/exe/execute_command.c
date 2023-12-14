/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:16:45 by edoardo           #+#    #+#             */
/*   Updated: 2023/12/14 15:29:01 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static void	find_delimiter(t_minishell *mini)
{
 	(void)mini;
	t_token *tmp = mini->start;
	while (tmp)
	{
		if (tmp->type == STOP)
		{
			if (tmp->next && tmp->next->type == ARG && tmp->next->str)
			{
				redirect_input_until(tmp->next->str);
			}
		}
		tmp = tmp->next;
	}
}

static void	creat_pipes(t_ppbx *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_number - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
		{
			perror("PIPE ERR");
			exit(0);
		}
		i++;
	}
}

void	exe_command(t_minishell *mini)
{
	int				i;

	i = -1;
	set_exe(mini);
	check_arg(mini);
	mini->exe->cmd_number = count_cmd(mini->start);
	mini->exe->pipe = (int *)malloc(sizeof(int) * 2 * (mini->exe->cmd_number));
	creat_pipes(mini->exe);
	while (++i < mini->exe->cmd_number)
	{
		if (ft_strcmp(mini->start->str,"exit") == 0)
			free_all(mini);
		else
			exe_cmd(mini, i);
	}
	close_pipes(mini->exe);
	free(mini->exe->filein);
	free(mini->exe->fileout);
	waitpid(-1,NULL,0);
}

void	exe_cmd(t_minishell *p, int n)
{
	p->exe->cmd = parse_cmd(p->start, n);
	p->exe->cmd_path = return_path(p->exe->cmd[0], token_to_matrix(p->env_start));
	p->exe->pid = fork();
	if (p->exe->pid == 0)
	{
		signal(SIGINT, child_signals);
		if (sub_dup2(n, p->exe) == -1)
		{
			free(p->exe->cmd_path);
			free_matrix(p->exe->cmd);
			close_pipes(p->exe);
			exit(1);
		}
		if (is_builtin(return_cmd(p->start, n)->str) == 1)
		{
			close_pipes(p->exe);
			if (!p->exe->cmd || !p->exe->cmd_path)
				exit(1);
			execve(p->exe->cmd_path, p->exe->cmd, token_to_matrix(p->env_start));
			printf("%s command not found\n",return_cmd(p->start, n)->str);		
		}
		else
			builtins(p,return_cmd(p->start, n));
	}
	free_matrix(p->exe->cmd);
	free(p->exe->cmd_path);
}

void	set_exe(t_minishell *mini)
{
	find_infile(mini);
	find_outfile(mini);
	find_delimiter(mini);
}
