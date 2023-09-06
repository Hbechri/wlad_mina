/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:57:34 by amakhrou          #+#    #+#             */
/*   Updated: 2022/11/08 16:36:07 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		l;
	char	*p;
	int		i;

	i = 0;
	l = ft_strlen(s1);
	if (s1 == NULL)
		return (NULL);
	p = malloc(l + 1);
	if (p == NULL)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
