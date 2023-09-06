/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 10:47:20 by amakhrou          #+#    #+#             */
/*   Updated: 2022/11/09 09:39:26 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (size && count >= SIZE_MAX / size)
		return (NULL);
	p = malloc(size * count);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, (count * size));
	return (p);
}
