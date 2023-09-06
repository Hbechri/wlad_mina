/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:29:42 by amakhrou          #+#    #+#             */
/*   Updated: 2022/11/08 16:38:43 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	t;

	if (!(s1 || set))
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	t = ft_strlen(s1);
	while (t && ft_strchr(set, s1[t]))
		t--;
	return (ft_substr(s1, 0, (t + 1)));
}
