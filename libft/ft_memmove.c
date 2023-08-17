/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:39:12 by hbechri           #+#    #+#             */
/*   Updated: 2022/11/15 15:55:40 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dt;
	unsigned char	*sr;

	dt = (unsigned char *)dst;
	sr = (unsigned char *)src;
	if (dt > sr)
	{
		while (len > 0)
		{
			dt[len - 1] = sr[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(dt, sr, len);
	return (dst);
}
