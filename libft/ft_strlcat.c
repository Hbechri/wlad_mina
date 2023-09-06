/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:57:51 by amakhrou          #+#    #+#             */
/*   Updated: 2022/11/07 15:24:35 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ld;
	size_t	ls;

	i = 0;
	ls = ft_strlen(src);
	if (!dstsize || dstsize <= ft_strlen(dst))
		return (ls + dstsize);
	ld = ft_strlen(dst);
	while (src[i] && i < dstsize - ld - 1)
	{
		dst[ld + i] = src[i];
		i++;
	}
	dst[ld + i] = '\0';
	return (ld + ls);
}
