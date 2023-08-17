/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:56:43 by hbechri           #+#    #+#             */
/*   Updated: 2022/11/14 19:46:07 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dt;
	unsigned char	*sr;

	if (dst == src)
		return (dst);
	if (!dst && !src)
		return (0);
	dt = (unsigned char *)dst;
	sr = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dt[i] = sr[i];
		i++;
	}
	return (dst);
}
