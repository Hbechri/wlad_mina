/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output_append.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:38:32 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/14 19:17:23 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redirect_output_append(t_command *cmd)
{
	t_redirection	*append;
	int				fd;

	while (cmd)
	{
		append = cmd->redirection;
		while (append)
		{
			if (append->type == APPEND_ID)
			{
				fd = open(append->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd == -1)
				{
					perror("open");
					g_exit_status = 1;
					exit(g_exit_status);
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			append = append->next;
		}
		cmd = cmd->next;
	}
}
