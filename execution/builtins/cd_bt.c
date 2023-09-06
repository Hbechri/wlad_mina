/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:34:27 by hbechri           #+#    #+#             */
/*   Updated: 2023/08/18 18:34:27 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*home_path(t_env_lst **env)
{
	t_env_lst	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp("HOME", tmp->key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	old_and_current_wd(t_env_lst *env, char *old_pwd, char *current_pwd)
{
	t_env_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp("OLDPWD", tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = old_pwd;
		}
		if (ft_strcmp("PWD", tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = current_pwd;
		}
		tmp = tmp->next;
	}
}

int	get_home_dir(t_env_lst *env)
{
	char	*home;

	home = home_path(&env);
	if (!home)
	{
		ft_putstr_fd("HOME not sett\n", 2);
		g_exit_status = 1;
		return (g_exit_status);
	}
	if (chdir(home) == 0)
		g_exit_status = 0;
	//to hundle export home="sfsfsf" or unset home and export home="sfsfsf"
	else
	{
		perror("haha"); //cd : no such file or directory
		g_exit_status = 1;
		return (g_exit_status);
	}
	return (g_exit_status);
}

int	cd_bt(char **av, t_env_lst *env)
{
	char	*old_pwd;
	char	*current_pwd;
	char	*buf;
	t_env_lst	*tmp;

	tmp = env;
	buf = NULL;
	old_pwd = getcwd(buf, 0);
	free(buf);
	if (av[1] == NULL || av[1][0] == '\0')
		get_home_dir(env);
	else if (chdir(av[1]) == 0)
	{
		current_pwd = getcwd(buf, 0);
		old_and_current_wd(env, old_pwd, current_pwd);
		g_exit_status = 0;
		return (g_exit_status);
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(av[1], 2);
		perror(" ");
		g_exit_status = 1;
	}
	return (g_exit_status);
}
