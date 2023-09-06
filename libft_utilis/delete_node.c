/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:57:25 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/06 15:58:37 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_node(t_env_lst *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}
