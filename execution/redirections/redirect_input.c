/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:00:28 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/06 19:02:14 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// <

void	redirect_input(t_command  *cmd)
{
	t_redirection  *in;

	in = cmd->redirection;
	while (in)
	{
		if (in->type == IN_ID)
		{
			in->fd = open(in->file, O_RDONLY);
			if (in->fd == -1) // error
				return ;
			dup2(in->fd, STDIN_FILENO);
			close(in->fd);
			break ;
		}
		in = in->next;
	}
}

