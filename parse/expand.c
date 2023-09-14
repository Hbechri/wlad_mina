/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:24:24 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/13 18:25:49 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_exit(t_lexer *lexer)
{
	lexer_advance(lexer);
	return (ft_itoa(g_exit_status));
}

char	*expandcheck(t_lexer *lexer, char *s, t_env_lst **env_dyalna)
{
	char	*tmp;

	if (lexer->c == '$')
	{
		tmp = expand_inside_word(lexer, env_dyalna);
		s = ft_strjoin(s, tmp);
		free(tmp);
	}
	if ((lexer->c == ' ' ) || (s && s[0] == '\0'))
	{
		tmp = ft_strdup(" ");
		s = ft_strjoin(s, tmp);
		free(tmp);
	}
	if (lexer->c == '\'' || lexer->c == '\"')
	{
		tmp = join_string(lexer, lexer->c, env_dyalna);
		s = ft_strjoin(s, tmp);
		free(tmp);
	}
	return (s);
}

char	*expand_inside_word(t_lexer *lexer, t_env_lst **env_dyalna)
{
	char	*val;
	char	*s;

	lexer_advance(lexer);
	if (lexer->c == '\"' || lexer->c == '$'
		|| lexer->c == ' ' || lexer->c == '\0' )
		return (ft_strdup("$"));
	if (lexer->c == '?')
		return (expand_exit(lexer));
	val = ft_strdup("");
	while (!if_operator(lexer->c) && !is_space(lexer->c)
		&& lexer->c != '\0' && lexer->c != '$' && lexer->c
		!= '\'' && lexer->c != '\"' && !if_special_char(lexer->c))
	{
		s = tokenz_value(lexer);
		val = ft_strjoin(val, s);
		free(s);
		lexer_advance(lexer);
	}
	s = my_getenv(val, env_dyalna);
	free(val);
	s = expandcheck(lexer, s, env_dyalna);
	return (s);
}

char	*expand_check_forfree(t_lexer *lexer, char *s, t_env_lst **env_dyalna)
{
	char	*tmp;

	if (lexer->c == '$')
	{
		tmp = expand_inside_quotes(lexer, env_dyalna);
		s = ft_strjoin(s, tmp);
		free(tmp);
	}
	return (s);
}

char	*expand_inside_quotes(t_lexer *lexer, t_env_lst **env_dyalna)
{
	char	*val;
	char	*s;

	lexer_advance(lexer);
	if (lexer->c == '\"' || lexer->c == ' ' || lexer->c == '$')
		return (ft_strdup("$"));
	if (lexer->c == '?')
		return (expand_exit(lexer));
	val = ft_strdup("");
	while (lexer->c != '\"' && lexer->c != ' '
		&& lexer->c != '\0' && lexer->c != '$' && lexer->c != '\''
		&& !if_special_char(lexer->c))
	{
		s = tokenz_value(lexer);
		val = ft_strjoin(val, s);
		free(s);
		lexer_advance(lexer);
	}
	s = my_getenv(val, env_dyalna);
	free(val);
	s = expand_check_forfree(lexer, s, env_dyalna);
	return (s);
}
