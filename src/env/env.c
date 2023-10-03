/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:09:17 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/03 15:25:34 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void make_env(t_minishell *minishell,  char **env)
{
    t_token *tmp;

    tmp->str = minishell->env[0];

    printf("%s\n", env[0]);



    minishell->env_start = tmp;
}