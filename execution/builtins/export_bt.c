/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 21:35:24 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/12 23:51:08 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	non_numeric(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return(1);
	return(0);
}

int	alphanum_c(char c)
{
	if (non_numeric(c) == 1)
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char *keyword(char *cmd)
{
	int i;
	char *key;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	key = ft_substr(cmd, 0, i);
	return (key);
}

char *value(char *cmd)
{
	int i;
	char *value;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	if (cmd[i] == '=' && cmd[i + 1] == '\0')
		value = ft_strdup("\r");
	else if (cmd[i] == '=' && cmd[i + 1] != '\0')
		value = ft_substr(cmd, i + 1, ft_strlen(cmd));
	else
		value = ft_strdup("");
	return (value);
}



int	key_checker(t_env_lst *env, char *key, char *val)
{
	t_env_lst *tmp;
	
	tmp = env;
	while(tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0 && val[0] != '\0' && val[0] != '\r')
		{
			free(tmp->value);
			tmp->value = ft_strdup(val);
			return (1);
		}
		else if (ft_strcmp(key, tmp->key) == 0 && (val[0] == '\0' || val[0] == '\r'))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	key_checker_plus(t_env_lst *env, char *key, char *val)
{
	t_env_lst *tmp;
	
	tmp = env;
	if (key[ft_strlen(key) - 1] == '+')
	{
		key[ft_strlen(key) - 1] = '\0';
		while(tmp)
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
		if(tmp->value[0] == '\r')
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

int	is_valid_key(t_env_lst *env, char *key, char *val)
{
	if (non_numeric(key[0]) == 1)
	{
		if(val == NULL)
			ft_lstadd_back(&env, ft_lstnew(key, NULL));
		else if (val)
			ft_lstadd_back(&env, ft_lstnew(key, val));
		return (1);
	}
	return (0);
}

void	export_error(char *key, char *val)
{
	ft_putstr_fd("minishell : `", 2);
	ft_putstr_fd(key, 2);
	if (val[0] != '\0')
	{
		ft_putstr_fd("=", 2);
		ft_putstr_fd(val, 2);
	}
	ft_putstr_fd("': not a valid identifier\n", 2);
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
	char *key;
	char *val;

	tmp = env;	
	int i = 1;
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
