/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:54:45 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/14 16:10:28 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void ignore_signal_for_shell(t_minishell *mini)
{	
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, INThandler);
}

void	INThandler(int sig)
{
	extern t_sig	g_sig;

	(void)sig;
	ft_putstr_fd("\b\b  ", 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(PROMPT,2);
	g_sig.exit_status = 130;
}

void init_signal()
{
	extern t_sig	g_sig;

	(void)g_sig;
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.exit_status = 0;
}