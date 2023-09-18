/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:54:45 by edoardo           #+#    #+#             */
/*   Updated: 2023/09/18 18:04:54 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void ignore_signal_for_shell()
{	
	// ignore "Ctrl-C"
    signal(SIGINT, SIG_IGN);
	// ignore "Ctrl-\"
    signal(SIGQUIT, SIG_IGN);
}