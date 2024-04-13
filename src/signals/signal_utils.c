/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:10:54 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/27 21:28:31 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parse_signal(int s)
{
	if (WIFSIGNALED(s))
		return ((int)(128 + WTERMSIG(s)));
	else if (WIFEXITED(s))
		return ((int)WEXITSTATUS(s));
	else
		return (s);
}
