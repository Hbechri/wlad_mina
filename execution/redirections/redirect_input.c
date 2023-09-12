/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:00:28 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/12 15:47:46 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// <

void	redirect_input(t_command  *cmd)
{
	t_redirection  *in;
	int fd;

	in = cmd->redirection;
	while (in)
	{
		if (in->type == IN_ID)
		{
			fd = open(in->file, O_RDONLY);
			if (fd == -1) // error
				return ;
			dup2(fd, STDIN_FILENO);
			close(fd);
			break ;
		}
		in = in->next;
	}
}

