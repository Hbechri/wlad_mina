/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:34:20 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/06 18:54:14 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset_bt(char **cmd, t_env_lst *env)
{
	int		i;
	t_env_lst	*tmp;
	t_env_lst	*prev;

	i = 1;
	//hundle the non alphanumeric case and '_'
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
				free(tmp->key);
				free(tmp->value);
				free(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}
