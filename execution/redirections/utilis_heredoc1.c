/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_heredoc1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:58:52 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/14 21:06:14 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*heredoc_file_name(void)
{
	int		fd;
	char	*file_name;
	char	*tmp;
	int		random;
	char	*random_str;

	fd = open("/dev/random", O_RDONLY);
	read(fd, &random, sizeof(rand));
	if (random < 0)
		random *= -1;
	random_str = ft_itoa(random);
	tmp = ft_strjoin_unfreeable("/tmp/", random_str);
	file_name = ft_strdup(tmp);
	close(fd);
	free(random_str);
	free(tmp);
	return (file_name);
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

void	heredoc_boucle(char *delimiter, int fd, t_env_lst **env, t_command *cmd)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		if (line)
		{
			if (cmd->dlm == 0)
			{
				tmp = expand_in_hdc(line, env);
				write(fd, tmp, ft_strlen(tmp));
				free(tmp);
			}
			else if (cmd->dlm == 1)
				write(fd, line, ft_strlen(line));
		}
		write(fd, "\n", 1);
	}
	close(fd);
	free(delimiter);
}

char	*set_delimiter(t_redirection *heredoc)
{
	char	*delimiter;
	char	*delimiter_tmp1;
	char	*delimiter_tmp2;

	delimiter_tmp1 = heredoc->file;
	delimiter_tmp2 = ignore_spaces(delimiter_tmp1);
	delimiter = remove_quotes(delimiter_tmp2);
	free(delimiter_tmp2);
	return (delimiter);
}

void	pid_error(void)
{
	perror("fork");
	exit(1);
}
