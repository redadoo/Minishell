/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:41:40 by edoardo           #+#    #+#             */
/*   Updated: 2023/09/24 16:24:50 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void free_matrix(char **matrix)
{
    int     i;

    i = 0;
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}

size_t len_matrix(char **matrix)
{
    int i;

    i = 0;
    if (matrix)
    {
        while (matrix[i])
            i++;
    }
    return i;
}
