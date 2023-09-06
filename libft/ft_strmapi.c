/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:08:37 by amakhrou          #+#    #+#             */
/*   Updated: 2022/11/08 16:37:36 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		l;
	int		i;
	char	*st;

	if (!s || !f)
		return (NULL);
	i = 0;
	l = ft_strlen(s);
	st = malloc (sizeof(char) * (l + 1));
	if (!st)
		return (NULL);
	while (s[i])
	{
		st[i] = f(i, s[i]);
		i++;
	}
	st[i] = '\0';
	return (st);
}
