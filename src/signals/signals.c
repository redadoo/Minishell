/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:54:45 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/04 18:16:00 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void ignore_signal_for_shell(t_sig	g_sig)
{	
	
	signal(SIGINT, INThandler);
}

void	INThandler(int sig)
{
	readline(PROMPT);
 	write(2,"\n",2);
	readline(PROMPT);
}

void init_signal(t_sig	g_sig)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.exit_status = 0;
}