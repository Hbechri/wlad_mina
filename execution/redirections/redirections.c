/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:39:29 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/12 15:37:41 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redirections(t_command *cmd, t_env_lst *env)
{
	t_redirection	*redirec;
	t_command		*tmp;

	tmp = cmd;
	while (tmp)
	{
		redirec = tmp->redirection;
		while(redirec)
		{
			if (redirec->type == IN_ID)
				redirect_input(tmp);
			else if (redirec->type == OUT_ID)
				redirect_output(tmp);
			else if (redirec->type == APPEND_ID)
				redirect_output_append(tmp);
			else if (redirec->type == HERDOC_ID)
				heredoc(tmp, env);
			redirec = redirec->next;
		}
		tmp = tmp->next;
	}
}