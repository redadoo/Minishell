/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:28:38 by edoardo           #+#    #+#             */
/*   Updated: 2023/12/23 14:59:43 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	redirect_input_until(char *del)
{
	char	*buff;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		buff = readline("> ");
		if (ft_strcmp(del, buff) == 0)
			break ;
		ft_putendl_fd(buff, fd[1]);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(buff);
}

void redirect_output(t_minishell *minishell, t_token *token)
{
	int	fd;

	(void)minishell;
	if (token->type == TRUNC)
		fd = open(token->next->str, O_TRUNC | O_CREAT | O_RDWR,0000644);
	else
		fd = open(token->next->str, O_APPEND | O_CREAT | O_RDWR, 0000644);
	dup2(fd,STDOUT_FILENO);
}

void redirect_input(t_minishell *minishell, t_token *token)
{
	(void)minishell;
	(void)token;
}