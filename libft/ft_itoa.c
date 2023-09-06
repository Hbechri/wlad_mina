/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:00:00 by amakhrou          #+#    #+#             */
/*   Updated: 2022/11/08 17:14:42 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	l_n(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t		l;
	int			i;
	char		*st;
	long int	r;

	i = 0;
	r = n;
	l = l_n(n);
	if (r < 0)
	{
		i = 1;
		r = r * -1;
	}
	st = malloc (sizeof(char) * (l + 1));
	if (!st)
		return (NULL);
	st[l] = '\0';
	while (l--)
	{
		st[l] = r % 10 + '0';
		r = r / 10;
	}
	if (i > 0)
		st[0] = '-';
	return (st);
}
