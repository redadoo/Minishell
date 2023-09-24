/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:32:19 by edoardo           #+#    #+#             */
/*   Updated: 2023/09/24 16:24:46 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void builtins(t_minishell *minishell)
{
    pid_t pid;

    pid = fork();

    if (strcmp(minishell->tokens[0], "echo") == 0)
        pwd();
}