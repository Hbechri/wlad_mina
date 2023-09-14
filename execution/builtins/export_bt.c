/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 21:35:24 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/14 20:51:14 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	key_checker(t_env_lst *env, char *key, char *val)
{
	t_env_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0 && val[0] != '\0')
		{
			free(tmp->value);
			tmp->value = ft_strdup(val);
			return (1);
		}
		else if (ft_strcmp(key, tmp->key) == 0
			&& (val[0] == '\0' || val[0] == '\r'))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	key_checker_plus(t_env_lst *env, char *key, char *val)
{
	t_env_lst	*tmp;

	tmp = env;
	if (key[ft_strlen(key) - 1] == '+')
	{
		key[ft_strlen(key) - 1] = '\0';
		while (tmp)
		{
			if (ft_strcmp(key, tmp->key) == 0)
			{
				tmp->value = ft_strjoin(tmp->value, val);
				return (1);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

void	export_lonely(t_env_lst *env)
{
	t_env_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->key, 1);
		if (tmp->value[0] == '\r')
			ft_putstr_fd("=\"\"", 1);
		else if (tmp->value && tmp->value[0] != '\0')
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}

void	export_boucle(t_env_lst *tmp, char *key, char *val)
{
	while (tmp)
	{
		if (key_checker_plus(tmp, key, val) == 1)
			break ;
		else if (key_checker(tmp, key, val) == 1)
			break ;
		else if (is_valid_key(tmp, key, val) == 1)
			break ;
		else
		{
			export_error(key, val);
			break ;
		}
		tmp = tmp->next;
	}
}

void	export_bt(char **cmd, t_env_lst *env)
{
	t_env_lst	*tmp;
	char		*key;
	char		*val;
	int			i;

	tmp = env;
	i = 1;
	if (!cmd[1])
		export_lonely(env);
	else
	{
		while (cmd[i])
		{
			key = keyword(cmd[i]);
			val = value(cmd[i]);
			tmp = env;
			export_boucle(tmp, key, val);
			free(key);
			free(val);
			i++;
		}
	}
}
