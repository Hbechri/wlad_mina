/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 01:38:08 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/15 01:40:37 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!dest || !src)
		return (NULL);
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
			dest[i] = src[j];
			i++;
			j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	int		len1;
	int		len2;
	int		len3;
	char	*strs;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	strs = (char *)malloc(len1 + len2 + len3 + 1);
	if (!strs)
		return (NULL);
	ft_strcpy(strs, s1);
	ft_strcat(strs, s2);
	ft_strcat(strs, s3);
	return (strs);
}
