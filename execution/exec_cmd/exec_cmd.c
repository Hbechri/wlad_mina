/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:56:03 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/08 17:41:13 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



void	exec_cmd(char **cmd, t_env_lst *env)
{
	char	**envp;
	char 	*path;
	char 	**splitted_paths;
	char	*tmp_path;
	int		i;

	i = 0;
	envp = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	while (env)
	{
		envp[i] = ft_strjoin(env->key, "=");
		envp[i] = ft_strjoin(envp[i], env->value);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	i = 0;
	if (cmd == NULL)
		return ;
	else
	{
		while(envp[i])
		{
			if (ft_strnstr(envp[i], "PATH", 4))
			{
				path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
				break ;
			}
			i++;
		}
		if (path)
		{
			splitted_paths = ft_split(path + 5, ':');
			i = 0;
			while (splitted_paths[i])
			{
				tmp_path = ft_strjoin(splitted_paths[i], "/");
				tmp_path = ft_strjoin(tmp_path, cmd[0]);
				if (access(tmp_path, F_OK) == 0)
				{
					execve(tmp_path, cmd, envp);
					break ;
				}
				i++;
			}
		}
	}
}
