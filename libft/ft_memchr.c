/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:48:59 by hbechri           #+#    #+#             */
/*   Updated: 2022/11/15 15:45:43 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			m;
	unsigned char	*chr;

	m = 0;
	chr = (unsigned char *)s;
	while (n > m)
	{
		if (chr[m] == (unsigned char)c)
			return (&chr[m]);
		m++;
	}
	return (0);
}
