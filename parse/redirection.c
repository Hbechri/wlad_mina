/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:26:54 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/06 16:46:58 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirection	*init_redirection(char *val, t_type type)
{
	t_redirection	*redirection;

	redirection = (t_redirection *)malloc(sizeof(t_redirection));
	redirection->file = ft_strdup(val);
	redirection->type = type;
	redirection->next = NULL;
	return (redirection);
}

void	new_redirecion(t_redirection *head, char *val, t_type type)
{
	t_redirection	*current;
	t_redirection	*new;

	current = head;
	while (current->next != NULL)
		current = current->next;
	new = malloc(sizeof(t_redirection));
	new->file = ft_strdup(val);
	new->type = type;
	new->next = NULL;
	current->next = new;
}
