/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:59:23 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/08 15:19:45 by hbechri          ###   ########.fr       */
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

void	heredoc(t_command *cmd)
{
	t_redirection *heredoc;
	char *line;
	char *delimiter;
	char *heredoc_file;
	pid_t pid;
	char *delimiter_tmp1;
	char *delimiter_tmp2;

	heredoc = cmd->redirection;
	while (heredoc)
	{
		if (heredoc->type == HERDOC_ID)
		{
			heredoc_file = heredoc_file_name();
			heredoc->hdc_file = ft_strdup(heredoc_file);
			// free(heredoc_file);
			heredoc->fd = open(heredoc->hdc_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			delimiter_tmp1 = heredoc->file;
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(1);
			}
			if (pid == 0)
			{
				delimiter_tmp2 = ignore_spaces(delimiter_tmp1);
				delimiter = remove_quotes(delimiter_tmp2);
				while (1)
				{
					line = readline("> ");
					if (!line)
						break ;
					if (ft_strcmp(line, delimiter) == 0)
						break ;
					if (line)
						write(heredoc->fd, line, ft_strlen(line));
					write(heredoc->fd, "\n", 1);
					free(line);
				}
				free(delimiter);
				close(heredoc->fd);
			}
			else
				waitpid(pid, NULL, 0);
		}
		heredoc = heredoc->next;
	}
}


// if << '$USER' == should not expand
// if << $USER == should expand
// if << "$USER" == should not expand
