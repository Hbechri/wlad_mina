/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:05:51 by amakhrou          #+#    #+#             */
/*   Updated: 2022/11/09 10:21:21 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;
	int				l;

	l = len - 1;
	if (dst > src)
	{
		s = (unsigned char *)src;
		d = (unsigned char *)dst;
		while (l >= 0)
		{
			d[l] = s[l];
			l--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
