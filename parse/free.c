/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:15:23 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/14 21:38:09 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redirections(t_redirection *rdr)
{
	t_redirection	*current;
	t_redirection	*temp;

	current = rdr;
	while (current)
	{
		free(current->file);
		temp = current;
		if (current->hdc_file)
		{
			unlink(current->hdc_file);
			free(current->hdc_file);
		}
		current = current->next;
		free(temp);
	}
}

void	free_env_lst(t_env_lst *env_lst)
{
	t_env_lst	*current;
	t_env_lst	*temp;

	current = env_lst;
	while (current)
	{
		free(current->key);
		free(current->value);
		temp = current;
		current = current->next;
		free(temp);
	}
}

void	free_cmd(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		i = 0;
		while (tmp->cmd && tmp->cmd[i])
		{
			free(tmp->cmd[i]);
			i++;
		}
		free(tmp->cmd);
		free_env_lst(tmp->envp);
		free_redirections(tmp->redirection);
		free(tmp);
	}
}
