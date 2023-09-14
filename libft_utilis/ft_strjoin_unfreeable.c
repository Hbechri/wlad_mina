/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_unfreeable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:36:34 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/14 19:02:43 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_unfreeable(char *s1, char *s2)
{
	size_t	l;
	char	*p;
	size_t	i;
	size_t	x;
	size_t	y;

	i = 0;
	x = 0;
	y = 0;
	l = ft_strlen(s1) + ft_strlen(s2);
	p = malloc(l + 1);
	if (p == NULL)
		return (NULL);
	while (s1[x])
	{
		p[i++] = s1[x++];
	}
	while (s2[y])
	{
		p[i++] = s2[y++];
	}
	p[i] = '\0';
	return (p);
}
