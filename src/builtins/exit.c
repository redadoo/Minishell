/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:37:38 by edoardo           #+#    #+#             */
/*   Updated: 2023/12/21 03:52:06 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"
#include "limits.h"

extern long long sig_exit_status;

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
	sig_exit_status = 2;
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

void    ft_exit(t_minishell * mini)
{
	ft_putendl_fd("exit", STDOUT_FILENO);

    if (mini->start->next && !mini->start->next->next)
    {
        if (check_status(mini->start->next->str))
		{
			if (!fits_in_longlong(mini->start->next->str))
				exit_non_numeric_arg();
			else
				sig_exit_status = ft_atoll(mini->start->next->str);
		}
		else
			exit_non_numeric_arg();
    }
    else if(mini->start->next->next)
    {
		sig_exit_status = EXIT_FAILURE;
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
    }
    else 
        sig_exit_status = EXIT_SUCCESS;
    free_matrix(mini->env);
	free_token(&mini->start, 0);
	free_token(&mini->env_start, 1);
	free(mini->exe);
	free(mini);
    exit(sig_exit_status); 
}
