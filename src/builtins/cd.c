/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:34:27 by fborroto          #+#    #+#             */
/*   Updated: 2024/03/25 15:59:40 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	update_path(t_minishell *mini)
{
	char	*str;
	char	cwd[PATH_MAX];

	str = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	change_env(mini, str);
	safe_free(str);
}

static int	update_oldpwd(t_minishell *mini)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (1);
	change_env(mini, oldpwd);
	safe_free(oldpwd);
	return (0);
}

static int	go_to_path(int option, t_minishell *mini)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(mini);
		env_path = ft_get_envar(find_var(mini->env_start, "HOME")->str);
		if (!env_path)
			ft_putendl_fd("minishell : cd: HOME not set", 2);
		if (!env_path)
			return (1);
	}
	else if (option == 1)
	{
		env_path = ft_get_envar(find_var(mini->env_start, "OLDPWD")->str);
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", 2);
		if (!env_path)
			return (1);
		update_oldpwd(mini);
	}
	ret = chdir(env_path);
	safe_free(env_path);
	return (ret);
}

int	cd(t_cmd *cmd, t_minishell *mini)
{
	int	cd_ret;

	if (!cmd->args[1])
		return (go_to_path(0, mini));
	if (cmd->args[2])
	{
		ft_putendl_fd("minishell : cd: too many arguments", 2);
		return (1);
	}
	if (ft_strcmp(cmd->args[1], "-") == 0)
		cd_ret = go_to_path(1, mini);
	else
	{
		update_oldpwd(mini);
		cd_ret = chdir(cmd->args[1]);
		update_path(mini);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
		{
			print_error("Error");
			return (1);
		}
	}
	return (0);
}
