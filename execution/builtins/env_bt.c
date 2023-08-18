/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:58:53 by hbechri           #+#    #+#             */
/*   Updated: 2023/08/17 19:50:42 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env_header.h"

void	env_bt(t_env_lst **env_lst)
{
	t_env_lst *node;

	node = *env_lst;
	while(node)
	{
		ft_putstr_fd(node->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(node->value, 1);
		ft_putstr_fd("\n", 1);
		node = node->next;
	}
}