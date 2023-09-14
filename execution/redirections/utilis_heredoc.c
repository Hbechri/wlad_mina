/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:57:46 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/14 22:39:36 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_alpha_and_underscore(char c)
{
	if (ft_isalpha(c) == 1)
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

char	*dollar_word(char *str)
{
	char	*word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word = NULL;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\0'
		&& is_alpha_and_underscore(str[i]) == 1)
		i++;
	word = ft_calloc(sizeof(char), (i + 1));
	while (j < i)
	{
		word[j] = str[j];
		j++;
	}
	word[i] = '\0';
	return (word);
}

char	*replace_with_value(char *line, char *word, t_env_lst **env)
{
	char	*value;
	char	*tmp;
	char	*tmp1;
	int		i;

	i = 0;
	value = my_getenv(word, env);
	while (line[i] != '$')
		i++;
	tmp = ft_substr(line, 0, i);
	tmp1 = ft_strjoin(tmp, value);
	tmp = ft_strjoin(tmp1, line + i + 1 + ft_strlen(word));
	free(value);
	return (tmp);
}

char	*expand_in_hdc(char *exp, t_env_lst **env)
{
	char	*expd;
	char	*word;
	char	*tmp;
	int		i;

	i = 0;
	expd = exp;
	while (expd[i])
	{
		if (expd[i] == '$')
		{
			word = dollar_word(expd + i + 1);
			tmp = replace_with_value(expd, word, env);
			free(expd);
			expd = ft_strdup(tmp);
			free(tmp);
			free(word);
		}
		i++;
	}
	return (expd);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(sizeof(char), (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		else
		{
			tmp[j] = str[i];
			i++;
			j++;
		}
	}
	tmp[j] = '\0';
	return (tmp);
}
