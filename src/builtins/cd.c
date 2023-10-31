/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:34:27 by fborroto          #+#    #+#             */
/*   Updated: 2023/10/31 14:53:02 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../lib/minishell.h"

// static void		print_error(t_token *token)
// {
// 	ft_putstr_fd("cd: ", 2);
// 	ft_putstr_fd(strerror(errno), 2);
// 	ft_putstr_fd(": ", 2);
// 	ft_putendl_fd(token->str, 2);
// }

// static char		*get_env_path(t_token *env, const char *var, size_t len)
// {
// 	char	*oldpwd;
// 	int		i;
// 	int		j;
// 	int		s_alloc;

// 	while (env && env->next != NULL)
// 	{
// 		if (ft_strncmp(env->value, var, len) == 0)
// 		{
// 			s_alloc = ft_strlen(env->value) - len;
// 			if (!(oldpwd = malloc(sizeof(char) * s_alloc + 1)))
// 				return (NULL);
// 			i = 0;
// 			j = 0;
// 			while (env->value[i++])
// 			{
// 				if (i > (int)len)
// 					oldpwd[j++] = env->value[i];
// 			}
// 			oldpwd[j] = '\0';
// 			return (oldpwd);
// 		}
// 		env = env->next;
// 	}
// 	return (NULL);
// }

// static int		update_oldpwd(t_token *env)
// {
// 	char	cwd[PATH_MAX];
// 	char	*oldpwd;

// 	if (getcwd(cwd, PATH_MAX) == NULL)
// 		return (ERROR);
// 	if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
// 		return (ERROR);
// 	if (is_in_env(env, oldpwd) == 0)
// 		add_to_env(&env, oldpwd, 1);
// 	ft_memdel(oldpwd);
// 	return (SUCCESS);
// }

// static int		go_to_path(int option, t_token *env)
// {
// 	int		ret;
// 	char	*env_path;

// 	env_path = NULL;
// 	if (option == 0)
// 	{
// 		update_oldpwd(env);
// 		env_path = get_env_path(env, "HOME", 4);
// 		if (!env_path)
// 			ft_putendl_fd("minishell : cd: HOME not set", 2);
// 		if (!env_path)
// 			return (1);
// 	}
// 	else if (option == 1)
// 	{
// 		env_path = get_env_path(env, "OLDPWD", 6);
// 		if (!env_path)
// 			ft_putendl_fd("minishell : cd: OLDPWD not set", 2);
// 		if (!env_path)
// 			return (1);
// 		update_oldpwd(env);
// 	}
// 	ret = chdir(env_path);
// 	ft_memdel(env_path);
// 	return (ret);
// }

// int				ft_cd(t_token *tokens, t_token *env)
// {
// 	int		cd_ret;
    
// 	if (!(tokens->next) || tokens->next->value != 2)
// 		return (go_to_path(0, env));
//     tokens = tokens->next;
//     if (tokens->next && tokens->next->type == 2)
//         ft_putendl_fd("minishell : cd: Too many arguments", 2);
// 	if (ft_strcmp(tokens->str, "-") == 0)
// 		cd_ret = go_to_path(1, env);
// 	else
// 	{
// 		update_oldpwd(env);
// 		cd_ret = chdir(tokens->str);
// 		if (cd_ret < 0)
// 			cd_ret *= -1;
// 		if (cd_ret != 0)
// 			//print_error(env);
// 	}
// 	return (cd_ret);
// }