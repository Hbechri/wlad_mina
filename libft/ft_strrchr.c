/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:42:01 by hbechri           #+#    #+#             */
/*   Updated: 2022/10/27 21:44:59 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*chr;

	len = ft_strlen(s);
	chr = (char *)s;
	while (len >= 0)
	{
		if (chr[len] == (char)c)
			return (&chr[len]);
		len--;
	}
	if ((char)c == '\0')
		return (&chr[len]);
	return (0);
}
