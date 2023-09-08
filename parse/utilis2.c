/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:38:13 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/08 17:40:12 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	array_len(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
			i++;
	}
	return (i);
}

int	token_array_lenght(t_token **token)
{
	int	i;

	i = 0;
	if (token)
	{
		while (token[i] != NULL)
			i++;
	}
	return (i);
}
