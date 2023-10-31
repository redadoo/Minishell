/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:16:45 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/31 18:34:14 by fborroto         ###   ########.fr       */
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
	int	i;

	i = -1;
	set_exe(mini);
	check_arg(mini);
	mini->exe->cmd_number = count_cmd(mini->start);
	mini->exe->pipe = (int *)malloc(sizeof(int) * 2 * (mini->exe->cmd_number));
	creat_pipes(mini->exe);
	while (++i < mini->exe->cmd_number)
	{
		exe_cmd(mini, i);
		waitpid(-1, NULL, 0);
	}
	close_pipes(mini->exe);
	free(mini->exe->filein);
	free(mini->exe->fileout);
}

void	exe_cmd(t_minishell *p, int n)
{
	char	**env;

	env = token_to_matrix(p->env_start);
	p->exe->cmd = parse_cmd(p->start, n);
	p->exe->cmd_path = return_path(p->exe->cmd[0], env);
	p->exe->pid = fork();
	if (p->exe->pid == 0)
	{
		if (sub_dup2(n, p->exe) == -1)
		{
			free(p->exe->cmd_path);
			free_matrix(p->exe->cmd);
			close_pipes(p->exe);
			exit(1);
		}
		if (access(p->exe->cmd_path, F_OK) == -1 && builtins(p, return_cmd(p->start, n)) == false)
		{
			write(2, p->exe->cmd[0], ft_strlen(p->exe->cmd[0]));
			write(2, " command not found\n", 20);
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
			execve(p->exe->cmd_path, p->exe->cmd, env);
		}
	}
	free_matrix(p->exe->cmd);
	free(p->exe->cmd_path);
	free_matrix(env);
}

void	set_exe(t_minishell *mini)
{
	find_infile(mini);
	find_outfile(mini);
}
