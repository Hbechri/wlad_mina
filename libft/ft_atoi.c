/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:58:00 by amakhrou          #+#    #+#             */
/*   Updated: 2022/11/08 15:38:50 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					o;
	int					c;
	unsigned long long	p;

	o = 0;
	c = 1;
	p = 0;
	while ((str[o] >= 9 && str[o] <= 13) || (str[o] == 32))
		o++;
	if (str[o] == '-')
		c = c * -1;
	if (str[o] == '-' || str[o] == '+')
		o++;
	while (str[o] >= '0' && str[o] <= '9')
	{
		p = p * 10 + (str[o] - '0');
		o++;
	}
	if (p >= 9223372036854775807 && c > 0)
		return (-1);
	if (p > 9223372036854775807 && c < 0)
		return (0);
	return (p * c);
}
