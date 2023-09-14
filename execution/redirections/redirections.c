/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:39:29 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/14 19:08:19 by hbechri          ###   ########.fr       */
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
		g_exit_status = 1;
		exit(g_exit_status);
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

void	dup_redi_in(t_command *cmd, int in_fd)
{
	t_redirection	*heredoc;
	int				check;

	check = 0;
	heredoc = cmd->redirection;
	while (heredoc)
	{
		if (heredoc->type == HERDOC_ID)
			check = 1;
		heredoc = heredoc->next;
	}
	if (check)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
}

void	redirections(t_command *cmd)
{
	t_redirection	*redirec;
	t_command		*tmp;
	int				in_fd;

	tmp = cmd;
	redirec = tmp->redirection;
	while (redirec)
	{
		in_fd = STDIN_FILENO;
		if (redirec->type == IN_ID)
			redirect_input(tmp);
		else if (redirec->type == OUT_ID)
			redirect_output(tmp);
		else if (redirec->type == APPEND_ID)
			redirect_output_append(tmp);
		else if (redirec->type == HERDOC_ID)
			in_fd = get_input_redirection_in_fd(redirec, in_fd);
		redirec = redirec->next;
	}
	dup_redi_in(cmd, in_fd);
}
