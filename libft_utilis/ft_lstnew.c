/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:54:19 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/06 15:55:47 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_lst	*ft_lstnew(char *keyword, char *value)
{
	t_env_lst	*list;

	list = (t_env_lst *)malloc((sizeof(t_env_lst)));
	if (list == NULL)
		return (NULL);
	list->key = ft_strdup(keyword);
	list->value = ft_strdup(value);
	list->next = NULL;
	return (list);
}
