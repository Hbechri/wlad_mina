/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:59:23 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/12 15:51:44 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*remove_quotes(char *str)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(sizeof(char), (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		else
		{
			tmp[j] = str[i];
			i++;
			j++;
		}
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*heredoc_file_name(void)
{
	int fd;
	char *file_name;
	char *tmp;
	int random;
	char *random_str;

	fd = open("/dev/random", O_RDONLY);
	read(fd, &random, sizeof(rand));
	if (random < 0)
		random *= -1;
	// random = random / 1000000;
	random_str = ft_itoa(random);
	tmp = ft_strjoin("/tmp/", random_str);
	file_name = ft_strdup(tmp);
	close(fd);
	free (random_str);
	free (tmp);
	return(file_name);
}

char	*ignore_spaces(char *str)
{
	char	*without_spaces;
	int		i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	without_spaces = ft_calloc(sizeof(char ), ((ft_strlen(str) - i) + 1));
	ft_strcpy(without_spaces, str + i);
	return (without_spaces);
}

void	heredoc_boucle(char *delimiter, int fd)
{
	char *line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		if (line)
			write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	free(delimiter);
}

char	*set_delimiter(t_redirection *heredoc)
{
	char *delimiter;
	char *delimiter_tmp1;
	char *delimiter_tmp2;

	delimiter_tmp1 = heredoc->file;
	delimiter_tmp2 = ignore_spaces(delimiter_tmp1);
	delimiter = remove_quotes(delimiter_tmp2);
	return (delimiter);
}

void	pid_error(void)
{
	perror("fork");
	exit(1);
}

int	set_heredoc_fd(t_redirection *heredoc)
{
	char *heredoc_file;
	int fd;

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

void	heredoc(t_command *cmd, t_env_lst *env)
{
	t_redirection *heredoc;
	char *delimiter;
	int fd;
	pid_t pid;

	(void)env;
	while (cmd)
	{
		heredoc = cmd->redirection;
		while(heredoc)
		{
			if (heredoc->type == HERDOC_ID)
			{
				fd = set_heredoc_fd(heredoc);
				pid = fork();
				if (pid == -1)
					pid_error();
				else if (pid == 0)
				{
					signal(SIGINT, SIG_DFL);
					signal(SIGINT, SIG_IGN);
					delimiter = set_delimiter(heredoc);
					heredoc_boucle(delimiter, fd);
					exit(0);
				}
				wait_signal(pid, fd);
			}
			heredoc = heredoc->next;
		}
		cmd = cmd->next;
	}
}


// if << '$USER' == should not expand
// if << $USER == should expand
// if << "$USER" == should not expand
