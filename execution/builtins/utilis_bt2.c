/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_bt2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:48:25 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/14 20:51:16 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	is_valid_key(t_env_lst *env, char *key, char *val)
{
	if (alpha_and_underscore(key))
	{
		if (val == NULL)
			ft_lstadd_back(&env, ft_lstnew(key, NULL));
		else if (val)
			ft_lstadd_back(&env, ft_lstnew(key, val));
		return (1);
	}
	return (0);
}

int	alpha_and_underscore(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (non_numeric(key[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

char	*keyword(char *cmd)
{
	int		i;
	char	*key;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	key = ft_substr(cmd, 0, i);
	return (key);
}

char	*value(char *cmd)
{
	int		i;
	char	*value;

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
