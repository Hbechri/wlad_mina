/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:34:33 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/14 21:09:56 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	option_checker(char *cmd, char option)
{
	int	i;

	i = 1;
	if (cmd[0] != '-' || ft_strlen(cmd) < 2)
		return (0);
	while (cmd[i])
	{
		if (cmd[i] != option)
			return (0);
		i++;
	}
	return (2);
}

int	echo_bt(char **cmd)
{
	int		i;
	int		nl_flag;

	nl_flag = 1;
	i = 1;
	while (cmd[i] && option_checker(cmd[i], 'n'))
	{
		nl_flag = 0;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1] == NULL)
			break ;
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (nl_flag == 1)
		printf("\n");
	return (0);
}
