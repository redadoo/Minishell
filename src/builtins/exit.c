/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:37:38 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/25 15:59:32 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "limits.h"

extern long long	g_exit_status;

static bool	fits_in_longlong(char *str)
{
	long long	out;
	int			c;

	if (ft_strlen(str) > 20)
		return (false);
	if (streq("-9223372036854775808", str))
		return (true);
	out = 0;
	if (*str == '-' || *str == '+')
		str += 1;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		c = *str - '0';
		if (out > (LLONG_MAX - c) / 10)
			return (false);
		out = out * 10 + c;
		str += 1;
	}
	return (true);
}

static void	exit_non_numeric_arg(void)
{
	g_exit_status = 2;
	ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
}

static bool	check_status(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (false);
		i += 1;
	}
	return (true);
}

void	ft_exit(t_minishell *mini, t_cmd *cmd)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd)
	{
		if (cmd->args[1] && !cmd->args[2])
		{
			if (check_status(cmd->args[1]))
			{
				if (!fits_in_longlong(cmd->args[1]))
					exit_non_numeric_arg();
				else
					g_exit_status = ft_atoll(cmd->args[1]);
			}
			else
				exit_non_numeric_arg();
		}
		else if (cmd->args[1] && cmd->args[2])
		{
			g_exit_status = EXIT_FAILURE;
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		}
		else
			g_exit_status = EXIT_SUCCESS;
	}
	free_all(mini);
}
