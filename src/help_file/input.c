
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:35:39 by edoardo           #+#    #+#             */
/*   Updated: 2023/09/24 16:23:49 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static bool check_command(t_minishell mini)
{
    
    return (false);
}

static void print_tokens(char **matrix)
{
    int i;

    i = -1;

    while (matrix[++i])
        printf("%s\n",matrix[i]);
}

void process_input(char *input,t_minishell *minishell)
{
    int     i;
    char    **tokens;

    i = 0;
    if (input == NULL)
        return ;
    minishell->tokens = ft_lexer(input);
    if (true)
        pipex(minishell);
    else
        builtins(minishell);
}