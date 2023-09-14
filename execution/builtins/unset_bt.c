/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:34:20 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/14 20:15:30 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_env(t_env_lst *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

void	unset_bt(char **cmd, t_env_lst *env)
{
	int			i;
	t_env_lst	*tmp;
	t_env_lst	*prev;

	i = 1;
	while (cmd[i])
	{
		tmp = env;
		prev = NULL;
		while (tmp)
		{
			if (ft_strcmp(cmd[i], tmp->key) == 0)
			{
				if (prev)
					prev->next = tmp->next;
				else
					env = tmp->next;
				free_env(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}
