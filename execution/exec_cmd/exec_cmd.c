/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:56:03 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/14 21:21:16 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*path_from_env(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			break ;
		}
		i++;
	}
	return (path);
}

char	*relative_path(char **cmd, char *splitted_paths)
{
	char	*tmp;
	char	*tmp_path;

	if (cmd[0][0] == '.' && cmd[0][1] == '/')
		no_such_file(cmd[0]);
	tmp_path = ft_strjoin(splitted_paths, "/");
	tmp = ft_strjoin(tmp_path, cmd[0]);
	return (tmp);
}

void	try_paths(char **splitted_paths, char **envp, char **cmd)
{
	int		i;
	int		flag;
	char	*tmp;

	i = 0;
	flag = 0;
	while (splitted_paths[i])
	{
		if (access(cmd[0], F_OK) == -1)
		{
			tmp = relative_path(cmd, splitted_paths[i]);
			if (access(tmp, F_OK) == 0)
			{
				flag = 1;
				if (execve(tmp, cmd, envp) == -1)
					cmd_not_found(cmd[0]);
			}
			free(tmp);
		}
		else if (access(*cmd, F_OK) == 0)
			execve(*cmd, cmd, envp);
		i++;
	}
	if (flag == 0)
		cmd_not_found(cmd[0]);
}

void	execute_command(char **cmd, char **envp)
{
	char	*path;
	char	**splitted_paths;

	if (valid_cmd(cmd[0]) == 1)
	{
		path = cmd[0];
		if (opendir(path))
			is_directory(cmd[0]);
	}
	path = path_from_env(envp);
	if (path)
	{
		splitted_paths = ft_split(path + 5, ':');
		try_paths(splitted_paths, envp, cmd);
	}
	else
	{
		if (access(cmd[0], F_OK) == 0)
			execve(cmd[0], cmd, envp);
		else
			cmd_not_found(cmd[0]);
	}
}

void	exec_cmd(char **cmd, t_env_lst *env)
{
	char	**envp;

	envp = env_table(env);
	if (cmd == NULL)
	{
		g_exit_status = 0;
		exit (g_exit_status);
	}
	else
		execute_command(cmd, envp);
}
