/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:59:21 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/06 16:05:52 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_env_lst **env_lst)
{
	t_env_lst	*tmp;
	t_env_lst	*node;

	node = *env_lst;
	while (node)
	{
		tmp = node->next;
		delete_node(node);
		node = tmp;
	}
	free(env_lst);
}
