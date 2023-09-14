/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:34:52 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/14 19:39:43 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd_bt(void)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
	{
		ft_putstr_fd("pwd: ", 2);
		ft_putstr_fd("error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		return (EX_FAILURE);
	}
	printf("%s\n", pwd);
	free (pwd);
	return (0);
}
