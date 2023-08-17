/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:08 by hbechri           #+#    #+#             */
/*   Updated: 2022/11/15 15:22:33 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*a;

	if (size && count >= SIZE_MAX / size)
		return (NULL);
	a = malloc(count * size);
	if (!a)
		return (0);
	ft_bzero(a, (count * size));
	return (a);
}
