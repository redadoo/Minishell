/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:16:45 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/29 17:46:56 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

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
	int		i;

	i = -1;
	set_exe(mini);
	check_arg(mini);
	mini->exe->cmd_number = count_cmd(mini->start) + 1;
	mini->exe->cmd_path = NULL;
	mini->exe->cmd = NULL;
	mini->exe->pipe = (int *)malloc(sizeof(int) * 2 * (mini->exe->cmd_number
				- 1));
	creat_pipes(mini->exe);
	while (++i < mini->exe->cmd_number - 1)
	{
		exe_cmd(mini, i);
	}
	close_pipes(mini->exe);
	waitpid(-1, NULL, 0);
}

void	exe_cmd(t_minishell *p, int n)
{
	p->exe->cmd = parse_cmd(p->start, n);
	p->exe->cmd_path = return_path(p->exe->cmd[0], p->env_start);
	p->exe->pid = fork();
	if (!p->exe->pid)
	{
		if (sub_dup2(n, p->exe) == -1)
		{
			free(p->exe->cmd_path);
			free_matrix(p->exe->cmd);
			close_pipes(p->exe);
			exit(1);
		}
		else
		{
			close_pipes(p->exe);
			if (!p->exe->cmd)
				exit(1);
			if (builtins(p, return_cmd(p->start, n)) == false)
				execve(p->exe->cmd_path, p->exe->cmd,
					token_to_matrix(p->env_start));
		}
	}
	free(p->exe->cmd_path);
	free_matrix(p->exe->cmd);
}

void	set_exe(t_minishell *mini)
{
	find_infile(mini);
	find_outfile(mini);
}
