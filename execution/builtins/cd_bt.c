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

int	pwd_oldpwd_checker(t_env_lst *env, char *old_pwd, char *current_pwd)
{
	t_env_lst	*tmp;

	tmp = env;
	if (!tmp)
	{
		free(current_pwd);
		free(old_pwd);
		return (0);
	}
	while (tmp)
	{
		if (strcmp(env->key, "PWD") != 0 || strcmp(env->key, "OLDPWD") != 0)
		{
			free(current_pwd);
			free(old_pwd);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

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
	if (pwd_oldpwd_checker(env, old_pwd, current_pwd) == 0)
		return ;
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
	else
	{
		perror("");
		g_exit_status = 1;
		return (g_exit_status);
	}
	return (g_exit_status);
}

int	cd_bt(char **cmd, t_env_lst *env)
{
	char	*old_pwd;
	char	*current_pwd;
	char	*buf;

	buf = NULL;
	old_pwd = getcwd(buf, 0);
	free(buf);
	if (cmd[1] == NULL || cmd[1][0] == '\0')
	{
		free(old_pwd);
		get_home_dir(env);
	}
	else if (chdir(cmd[1]) == 0)
	{
		current_pwd = getcwd(buf, 0);
		old_and_current_wd(env, old_pwd, current_pwd);
		g_exit_status = 0;
		return (g_exit_status);
	}
	else
		cd_error(cmd[1], old_pwd);
	return (g_exit_status);
}
