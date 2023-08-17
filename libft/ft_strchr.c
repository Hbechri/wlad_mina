/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:56:17 by hbechri           #+#    #+#             */
/*   Updated: 2023/01/21 13:52:24 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*chr;

	i = 0;
	chr = (char *)s;
	while (chr[i])
	{
		if (chr[i] == (char)c)
			return (&chr[i]);
		i++;
	}
	return (0);
}
