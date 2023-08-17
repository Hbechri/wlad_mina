/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:29:12 by hbechri           #+#    #+#             */
/*   Updated: 2022/11/15 14:51:38 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	words_num(const char *s, char c)
{
	int	co;
	int	i;

	i = 0;
	co = 0;
	while (s[i])
	{
		if (s[i] != c && ((s[i + 1] == c) || (s[i + 1] == '\0')))
		{
			co++;
		}
		i++;
	}
	return (co);
}

int	word_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*word_all(const char *str, char c)
{
	char	*s;
	int		i;
	int		len;

	i = 0;
	len = word_len(str, c);
	s = malloc((sizeof(char)) * (len + 1));
	if (!s)
		return (NULL);
	while (str[i] && str[i] != c && len > 0)
	{
		s[i] = str[i];
		i++;
		len--;
	}
	s[i] = '\0';
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	**table;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	table = malloc((sizeof(char *)) * (words_num(s, c) + 1));
	if (!table)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			table[j] = word_all(&s[i], c);
			i = i + word_len(&s[i], c);
			j++;
		}
	}
	table[j] = NULL;
	return (table);
}
