/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 21:35:24 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/06 18:56:55 by hbechri          ###   ########.fr       */
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
		value = ft_strdup("\0");
	return (value);
}

int	is_separator(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	key_with_plus(char *key)
{
	int i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '+' && key[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void	export_bt(char **cmd, t_env_lst *env)
{
	t_env_lst	*tmp;

	tmp = env;
	//static int flag = 1;
	
	if (!cmd[1])
	{
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
			// else if (flag == 1)
			// {
			// 	ft_putstr_fd("=\"\"", 1);
			// 	flag = 0;
			// }
			ft_putstr_fd("\n", 1);
			tmp = tmp->next;
		}
	}
	else
	{
		//flag = 0;
		char *key;
		char *val;
		int i = 1;
		while (cmd[i])
		{
			// if(is_separator(cmd[i]))
			// 	flag = 1;
			key = keyword(cmd[i]);
			val = value(cmd[i]);
			tmp = env;
			while (tmp)
			{
				if (ft_strcmp(key, tmp->key) == 0)
				{
					free(tmp->value);
					tmp->value = ft_strdup(val);
					break ;
				}
				else if (key_with_plus(key) == 1 && ft_strcmp(key, tmp->key) == 1)
				{
					tmp->value = ft_strjoin(tmp->value, val);
					break ;
				}
				else if ((non_numeric(key[0]) == 1) && (alphanum_c(key[1])))
				{
					if(val == NULL)
						ft_lstadd_back(&tmp, ft_lstnew(key, NULL));
					else if (val)
						ft_lstadd_back(&tmp, ft_lstnew(key, val));
					break ;
				}
				
				else
				{
					ft_putstr_fd("export: `", 2);
					ft_putstr_fd(key, 2);
					if (val)
					{
						ft_putstr_fd("=", 2);
						ft_putstr_fd(val, 2);
					}
					ft_putstr_fd("': not a valid identifier\n", 2);
					break ;
				}
				tmp = tmp->next;
			}
			i++;
		}
	}
}
