/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:56:03 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/08 23:06:09 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**env_table(t_env_lst *env)
{
	char	**envp;
	int	i;

	i = 0;
	envp = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (!envp)
		return(NULL);
	while (env)
	{
		envp[i] = ft_strjoin(env->key, "=");
		envp[i] = ft_strjoin(envp[i], env->value);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return(envp);
}

char	*path_from_env(char **envp)
{
	char	*path;
	int	i;

	i = 0;
	path = NULL;
	while(envp[i])
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

void	try_paths(char **splitted_paths, char **envp, char **cmd)
{

	char	*tmp_path;
	char *tmp;
	int	i;
	int flag;

	i = 0;
	flag = 0;
	while (splitted_paths[i])
	{
		if (access(cmd[0], F_OK) == -1)
		{
			tmp_path = ft_strjoin(splitted_paths[i], "/");
			tmp = ft_strjoin(tmp_path, cmd[0]);
			if (access(tmp, F_OK) == 0)
			{
				flag = 1;
				if (execve(tmp, cmd, envp) == -1)
				{
					ft_putstr_fd("minishell : ", 2);
					ft_putstr_fd (cmd[0], 2);
					ft_putstr_fd(" : No such file or directory\n", 2);
					return ;
				}
			}
		}
		else if (access(*cmd, F_OK) == 0)
			execve(*cmd, cmd, envp);
		i++;
	}
	if (flag == 0)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd (cmd[0], 2);
		ft_putstr_fd(" : command not found\n", 2);
		return ;
	}
}

void	exec_cmd(char **cmd, t_env_lst *env)
{
	char	**envp;
	char 	*path;
	char 	**splitted_paths;


	path = NULL;
	envp = env_table(env);
	if (cmd == NULL)
		return ;
	else
	{

		path = path_from_env(envp);

		if (path)
		{
			splitted_paths = ft_split(path + 5, ':');
			try_paths(splitted_paths, envp, cmd);
		}
	}
}
