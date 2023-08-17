/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:38:28 by hbechri           #+#    #+#             */
/*   Updated: 2022/10/28 15:45:57 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*chr1;
	unsigned char	*chr2;
	size_t			m;

	chr1 = (unsigned char *)s1;
	chr2 = (unsigned char *)s2;
	m = 0;
	while (n > 0)
	{
		if (chr1[m] != chr2[m])
			return (chr1[m] - chr2[m]);
		n--;
		m++;
	}
	return (0);
}
