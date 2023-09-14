/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:38:05 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/14 19:16:05 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redirect_output(t_command *cmd)
{
	t_redirection	*out;
	int				fd;

	while (cmd)
	{
		out = cmd->redirection;
		while (out)
		{
			if (out->type == OUT_ID)
			{
				fd = open(out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd == -1)
				{
					perror("open");
					g_exit_status = 1;
					exit(g_exit_status);
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			out = out->next;
		}
		cmd = cmd->next;
	}
}
