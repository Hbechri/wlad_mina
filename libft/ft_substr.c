/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:40:23 by amakhrou          #+#    #+#             */
/*   Updated: 2022/11/08 16:39:07 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	l;
	char	*p;
	size_t	i;

	i = 0;
	l = ft_strlen(s);
	if (len > l)
		len = l;
	if (start > l)
		return (ft_strdup(""));
	p = malloc(len + 1);
	if (p == NULL)
		return (NULL);
	while (s[start] && i < len)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}
