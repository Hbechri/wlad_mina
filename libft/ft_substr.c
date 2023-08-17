/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 20:20:50 by hbechri           #+#    #+#             */
/*   Updated: 2022/11/15 17:12:28 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*sb;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (len > slen)
		len = slen;
	if (start > slen)
		return (ft_strdup(""));
	sb = (char *) malloc(sizeof(char) * (len + 1));
	if (!sb)
		return (0);
	i = 0;
	while (s[start] && i < len)
	{
		sb[i] = s[start];
		i++;
		start++;
	}
	sb[i] = '\0';
	return (sb);
}
