/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:59:23 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/13 17:30:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	is_quotes(char *str)
// {
// 	int i;

// 	i = 0;
// 	while(str[i])
// 	{
// 		if (str[i] == '\'' || str[i] == '\"')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	is_alpha_and_unserscore_char(char c)
// {
// 	if (ft_isalpha(c) == 1)
// 		return (1);
// 	else if (c == '_')
// 		return (1);
// 	return (0);
// }

int	is_alpha_and_underscore(char c)
{
	if (ft_isalpha(c) == 1)
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

char	*dollar_word(char *str)
{
	char *word;
	int i;
	int j;

	i = 0;
	j = 0;
	word = NULL;
	while(str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\0'
		&& is_alpha_and_underscore(str[i]) == 1)
		i++;
	word = ft_calloc(sizeof(char), (i + 1));
	while (j < i)
	{
		word[j] = str[j];
		j++;
	}
	word[i] = '\0';
	return (word);
}

char	*replace_with_value(char *line, char *word, t_env_lst **env)
{
	char *value;
	char *tmp;
	char *tmp1;
	int i;

	i = 0;
	value = my_getenv(word, env);
	while (line[i] != '$')
		i++;
	tmp = ft_substr(line, 0, i);
	tmp1 = ft_strjoin(tmp, value);
	free(tmp);
	tmp = ft_strjoin(tmp1, line + i + 1 + ft_strlen(word));
	free(tmp1);
	return (tmp);
}


char	*expand_in_hdc(char *exp, t_env_lst **env)
{
	char *expd;
	char *word;
	char *tmp;
	int i;

	i = 0;
	expd = exp;
	while(expd[i])
	{
		if(expd[i] == '$')
		{
			word = dollar_word(expd + i + 1);
			tmp = replace_with_value(expd, word, env);
			free(expd);
			expd = ft_strdup(tmp);
			free(tmp);
			free(word);
		}
		i++;
	}
	return (expd);
}

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

void	heredoc_boucle(char *delimiter, int fd, t_env_lst **env, t_command *cmd)
{
	char *line;
	char *tmp;
	
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
		// free(line);
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
					heredoc_boucle(delimiter, fd, &env, cmd);
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
