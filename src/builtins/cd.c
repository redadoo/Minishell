/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:34:27 by fborroto          #+#    #+#             */
/*   Updated: 2023/12/16 20:01:20 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static void	print_error()
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("No such file or directory", 2);
}

static char	*get_env_path(t_token *env, const char *var, size_t len)
{
	char	*oldpwd;
	int		i;
	int		j;
	int		s_alloc;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->str, var, len) == 0)
		{
			s_alloc = ft_strlen(env->str) - len;
			oldpwd = malloc(sizeof(char) * s_alloc + 1);
			i = 0;
			j = 0;
			while (env->str[i++])
			{
				if (i > (int)len)
					oldpwd[j++] = env->str[i];
			}
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int	update_oldpwd(t_token *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (1);
	if (is_in_env(env, oldpwd) == 0)
	{
		free(find_var(env, oldpwd)->str);
		find_var(env, oldpwd)->str = strdup(oldpwd);
	}
	ft_memdele(oldpwd);
	return (0);
}

static int	go_to_path(int option, t_token *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME", 4);
		if (!env_path)
			ft_putendl_fd("minishell : cd: HOME not set", 2);
		if (!env_path)
			return (1);
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", 2);
		if (!env_path)
			return (1);
		update_oldpwd(env);
	}
	ret = chdir(env_path);
	ft_memdele(env_path);
	return (ret);
}

int	cd(t_token *tokens, t_token *env)
{
	int	cd_ret;

	if (!(tokens->next) || tokens->next->type != ARG)
		return (go_to_path(0, env));
	tokens = tokens->next;
	if (tokens->next && tokens->next->type == ARG)
	{
		ft_putendl_fd("minishell : cd: too many arguments", 2);
		return (1);
	}
	if (ft_strcmp(tokens->str, "-") == 0)
		cd_ret = go_to_path(1, env);
	else
	{
		update_oldpwd(env);
		cd_ret = chdir(tokens->str);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
		{
			print_error();
			return (1);
		}
	}
	return (0);
}
