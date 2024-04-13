/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:54:27 by edoardo           #+#    #+#             */
/*   Updated: 2024/03/28 12:33:52 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_io(t_manage_red *io)
{
	if (io)
	{
		safe_free(io->infile);
		safe_free(io->outfile);
		safe_free(io->hdc);
		safe_free(io);
	}
	else
		return ;
}
