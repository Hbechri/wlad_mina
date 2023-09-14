/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:00:28 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/14 19:09:48 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redirect_input(t_command *cmd)
{
	t_redirection	*in;
	int				fd;

	while (cmd)
	{
		in = cmd->redirection;
		while (in)
		{
			if (in->type == IN_ID)
			{
				fd = open(in->file, O_RDONLY);
				if (fd == -1)
				{
					perror("open");
					g_exit_status = 1;
					exit(g_exit_status);
				}
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			in = in->next;
		}
		cmd = cmd->next;
	}
}
