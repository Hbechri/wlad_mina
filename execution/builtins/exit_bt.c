/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:34:47 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/08 16:13:01 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_bt(char	**cmd)
{
	int	i;
	int j = 0;
	int num = 0;
	i = 0;
	while (cmd[i])
		i++;
	if (i == 1)
		exit(0);
	else if (i == 2)
	{
		while (cmd[1][j])
		{
			if (ft_isdigit(cmd[1][j]) == 0)
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(cmd[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(255);
			}
			j++;
		}
		if (ft_isdigit(cmd[1][0]) == 1)
			exit(ft_atoi(cmd[1]));
		else
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
	else
	{
		int flag = 0;
		i = 1;
		j = 0;
		while(cmd[i])
		{
			while (cmd[i][j])
			{
				if (ft_isdigit(cmd[i][j]) == 1)
					num++;
				j++;
			}
			if(num == j)
				flag += 1;
			j = 0;
			num = 0;
			i++;
		}
		if (flag == (i - 1))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		else
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
	return (0);
}
