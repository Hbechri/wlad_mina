/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:34:47 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/11 21:24:17 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_num_arg_req(char *cmd)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

void	exit_too_many_arg(void)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
}

void	exit_with_one_arg(char **cmd)
{
	int	j;

	j = 0;
	while (cmd[1][j])
	{
		if (ft_isdigit(cmd[1][j]) == 0)
			exit_num_arg_req(cmd[1]);
		j++;
	}
	if (ft_isdigit(cmd[1][0]) == 1)
		exit(ft_atoi(cmd[1]));
	else
		exit_num_arg_req(cmd[1]);
}

int	exit_arg_flag(char **cmd)
{
	int	j;
	int	num;
	int	flag;

	j = 0;
	num = 0;
	flag = 0;
	while (cmd[1][j])
	{
		if (ft_isdigit(cmd[1][j]) == 1)
			num++;
		j++;
	}
	if(num == j)
		flag = 1;
	return (flag);
}

int	exit_bt(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i == 1)
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	else if (i == 2)
		exit_with_one_arg(cmd);
	else
	{
		if (exit_arg_flag(cmd) == 1)
		{
			exit_too_many_arg();
			return (1);
		}
		else
			exit_num_arg_req(cmd[1]);
	}
	return (0);
}
