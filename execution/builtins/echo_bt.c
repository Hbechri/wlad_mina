/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:34:33 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/06 18:51:11 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

typedef enum e_excode
{
	EX_SUCCESS = 0,
	EX_FAILURE = 1,
	EX_BT_FAIL = 2,
	EX_CNOT_EXEC = 126,
	EX_CNOT_FIND = 127,
	EX_BY_SIGNAL = 128,
	EX_OUTOF_RANGE = 255
}	t_excode;

int	option_checker(char *cmd, char option)
{
	int	i;

	i = 2;
	if (cmd[0] != '-' || ft_strlen(cmd) < 2)
		return (EX_SUCCESS);
	while (cmd[i])
	{
		if (cmd[i] != option)
			return (EX_SUCCESS);
		i++;
	}
	return (EX_BT_FAIL);
}

int echo(char **cmd)
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
	return (EX_SUCCESS);
}
