/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_bt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:41:32 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/08 18:09:57 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bt_checker(t_command *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd->cmd[0], "echo") || (!ft_strcmp(cmd->cmd[0], "cd"))
		|| (!ft_strcmp(cmd->cmd[0], "pwd"))
		|| (!ft_strcmp(cmd->cmd[0], "export"))
		|| (!ft_strcmp(cmd->cmd[0], "unset"))
		|| (!ft_strcmp(cmd->cmd[0], "env"))
		|| (!ft_strcmp(cmd->cmd[0], "exit")))
		return (1);
	return (0);
}

void	exec_bt(t_command *cmd, t_env_lst *env)
{
	if (!cmd->cmd)
		return ;
	if (!ft_strcmp(cmd->cmd[0], "cd"))
		cd_bt(cmd->cmd, env);
	else if (!ft_strcmp(cmd->cmd[0], "echo"))
		echo_bt(cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		env_bt(env);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		exit_bt(cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		export_bt(cmd->cmd, env);
	else if (!ft_strcmp(cmd->cmd[0], "pwd"))
		pwd_bt();
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		unset_bt(cmd->cmd, env);
	else
		return ;
}
