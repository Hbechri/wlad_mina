/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 21:28:16 by hbechri           #+#    #+#             */
/*   Updated: 2022/11/14 21:53:33 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*sc;
	int		i;

	i = 0;
	sc = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!sc)
		return (0);
	while (s1[i])
	{
		sc[i] = s1[i];
		i++;
	}
	sc[i] = '\0';
	return (sc);
}
