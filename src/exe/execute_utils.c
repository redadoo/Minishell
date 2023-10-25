/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:50:04 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/25 22:52:38 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int find_infile(t_minishell *mini)
{
	t_token	*tmp;

	tmp = mini->start;
/* 	while (tmp)
	{
		if (tmp->type == CMD)
		{
			
		}
	} */
}

int find_outfile(t_minishell *mini)
{
    int     fd;
	t_token	*tmp;

	tmp = mini->start;
	while (tmp)
	{
		if (tmp->type == 3 || tmp->type == APPEND)
		{
			fd = open(tmp->next->str, O_TRUNC | O_CREAT | O_RDWR, 0000644);
            return (fd);
        }
	}
	return 0;
}

char	*return_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*cmd_path;
	char 	*tmp;
	i = 0;
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
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
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