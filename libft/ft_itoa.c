/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:06:10 by hbechri           #+#    #+#             */
/*   Updated: 2022/11/14 21:54:01 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_num_len(int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
		i++;
	if (n == 0)
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
	long int	nb;
	char		*str;
	size_t		len;

	nb = n;
	len = ft_num_len(nb);
	str = (char *)malloc((sizeof(char)) * len + 1);
	if (!str)
		return (0);
	str[len] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb > 0 && len > 0)
	{
		len--;
		str[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (str);
}
