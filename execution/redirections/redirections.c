/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:39:29 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/12 18:55:35 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	heredoc_file(t_redirection *redr)
{
	int	in_fd;

	in_fd = open(redr->hdc_file, O_RDONLY, 0644);
	if (in_fd == -1)
	{
		perror("open");
		exit(1);
	}
	return (in_fd);
}

int	get_input_redirection_in_fd(t_redirection *redr, int in_fd)
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	else if (redr->type == HERDOC_ID)
	{
		in_fd = heredoc_file(redr);
		return (in_fd);
	}
	return (in_fd);
}

void	dup_redi_in(t_command *cmd_list, int in_fd)
{
	t_redirection	*redirection;

	redirection = cmd_list->redirection;
	while (redirection)
	{
		if (redirection->type == HERDOC_ID)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		redirection = redirection->next;
	}
}

void	redirections(t_command *cmd, t_env_lst *env)
{
	t_redirection	*redirec;
	t_command		*tmp;
	int				in_fd;

	(void)env;
	in_fd = STDIN_FILENO;
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
			{
				// heredoc(tmp, env);
				in_fd = get_input_redirection_in_fd(redirec, in_fd);
				dup_redi_in(cmd, in_fd);
			}
			redirec = redirec->next;
		}
		tmp = tmp->next;
	}
}