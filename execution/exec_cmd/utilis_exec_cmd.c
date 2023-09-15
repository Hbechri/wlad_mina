/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_exec_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:39:26 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/15 01:58:03 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	no_such_file(char *cmd)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd (cmd, 2);
	ft_putstr_fd(" : No such file or directory\n", 2);
	g_exit_status = 127;
	exit (g_exit_status);
}

void	cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd (cmd, 2);
	ft_putstr_fd(" : command not found\n", 2);
	g_exit_status = 127;
	exit (g_exit_status);
}

void	is_directory(char *cmd, DIR *dir)
{
	closedir(dir);
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" : Is a directory\n", 2);
	g_exit_status = 126;
	exit (g_exit_status);
}

int	valid_cmd(char *cmd)
{
	if (cmd == NULL)
		return (0);
	else if (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
		return (1);
	else if (cmd[0] == '.' && cmd[1] == '/')
		return (1);
	else if (cmd[0] == '/')
		return (1);
	return (0);
}

char	**env_table(t_env_lst *env)
{
	char		**envp;
	int			i;
	int			j;
	t_env_lst	*tmp;

	i = 0;
	j = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	tmp = env;
	while (tmp)
	{
		envp[j] = ft_strjoin3(tmp->key, "=", tmp->value);
		j++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
