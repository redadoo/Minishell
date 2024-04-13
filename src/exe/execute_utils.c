/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:50:04 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/22 20:04:23 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipe(t_cmd *cmds, t_cmd *current_command)
{
	t_cmd	*tmp;

	tmp = cmds;
	if (!cmds)
		return ;
	while (tmp)
	{
		if (tmp != current_command && tmp->pipe_fd)
		{
			close(tmp->pipe_fd[0]);
			close(tmp->pipe_fd[1]);
		}
		tmp = tmp->next;
	}
}

void	set_dup2(t_cmd *command)
{
	if (!command)
		return ;
	if (command->prev && command->prev->pipe_output)
		dup2(command->prev->pipe_fd[0], STDIN_FILENO);
	if (command->pipe_output)
		dup2(command->pipe_fd[1], STDOUT_FILENO);
}

bool	init_pipe(t_minishell *minishell)
{
	t_cmd	*tmp;

	tmp = minishell->cmd;
	while (tmp)
	{
		if (tmp->pipe_output || (tmp->prev && tmp->prev->pipe_output))
		{
			tmp->pipe_fd = malloc(sizeof * tmp->pipe_fd * 2);
			if (!tmp->pipe_fd || pipe(tmp->pipe_fd) != 0)
				return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}

char	*return_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*cmd_path;
	char	*tmp;

	i = 0;
	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	while (env[i] && ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		cmd_path = paths[i];
		tmp = ft_strdup(paths[i]);
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, "/");
		free(tmp);
	}
	cmd_path = acces_command(cmd, paths);
	free_matrix(paths);
	return (cmd_path);
}

char	*acces_command(char *cmd_name, char **paths)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		if (cmd_path != NULL)
			free(cmd_path);
		cmd_path = ft_strjoin(paths[i], cmd_name);
		if (access(cmd_path, X_OK) == 0)
			break ;
		i++;
	}
	return (cmd_path);
}
