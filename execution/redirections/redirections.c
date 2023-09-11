/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:39:29 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/11 15:39:47 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redirections(t_command *cmd)
{
	t_redirection	*redirec;

	redirec = cmd->redirection;
	while (redirec)
	{
		if (redirec->type == IN_ID)
			redirect_input(cmd);
		else if (redirec->type == OUT_ID)
			redirect_output(cmd);
		else if (redirec->type == APPEND_ID)
			redirect_output_append(cmd);
		// else if (redirec->type == HERDOC_ID)
		// 	heredoc(cmd);
		redirec = redirec->next;
	}
}