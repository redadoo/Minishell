/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:35:39 by edoardo           #+#    #+#             */
/*   Updated: 2023/09/18 20:00:48 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

//TODO:-save input in history -process input -execute input
void process_input(char *input,t_minishell *minishell)
{
    int     i;
    char    **tokens;

    i = 0;
    if (input == NULL)
        return ;
    minishell->tokens = ft_lexer(input);
}