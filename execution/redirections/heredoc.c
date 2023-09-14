/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:59:23 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/14 21:06:00 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_heredoc_fd(t_redirection *heredoc)
{
	char	*heredoc_file;
	int		fd;

	heredoc_file = heredoc_file_name();
	heredoc->hdc_file = ft_strdup(heredoc_file);
	free(heredoc_file);
	fd = open(heredoc->hdc_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

int	wait_signal(int pid, int fd)
{
	int	status;

	close(fd);
	waitpid(pid, &status, 0);
	g_exit_status = get_exit_status(status);
	return (0);
}

void	heredoc_setup(t_command *cmd, t_env_lst *env, t_redirection *heredoc)
{
	int		fd;
	pid_t	pid;
	char	*delimiter;

	fd = set_heredoc_fd(heredoc);
	pid = fork();
	if (pid == -1)
		pid_error();
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		delimiter = set_delimiter(heredoc);
		heredoc_boucle(delimiter, fd, &env, cmd);
		exit(0);
	}
	wait_signal(pid, fd);
}

void	heredoc(t_command *cmd, t_env_lst *env)
{
	t_redirection	*heredoc;

	while (cmd)
	{
		heredoc = cmd->redirection;
		while (heredoc)
		{
			if (heredoc->type == HERDOC_ID)
				heredoc_setup(cmd, env, heredoc);
			heredoc = heredoc->next;
		}
		cmd = cmd->next;
	}
}
