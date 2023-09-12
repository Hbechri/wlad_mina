/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:24:24 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/11 21:07:44 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_exit(t_lexer *lexer)
{
	lexer_advance(lexer);
	return (ft_itoa(g_exit_status));
	// return NULL;
}

char	*expandcheck(t_lexer *lexer, char *s, t_env_lst **env_dyalna)
{
	if (lexer->c == '$')
		s = ft_strjoin(s, expand_inside_word(lexer, env_dyalna));
	if ((lexer->c == ' ' ) || (s && s[0] == '\0'))
		s = ft_strjoin(s, ft_strdup(" "));
	if (lexer->c == '\'' || lexer->c == '\"')
		s = ft_strjoin(s, join_string(lexer, lexer->c, env_dyalna));
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
		!= '\'' && lexer->c != '\"' && lexer->c != '=')
	{
		s = tokenz_value(lexer);
		val = ft_strjoin(val, s);
		lexer_advance(lexer);
	}
	s = my_getenv(val, env_dyalna);
	free(val);
	s = expandcheck(lexer, s, env_dyalna);
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
		&& lexer->c != '\0' && lexer->c != '$' && lexer->c != '\'')
	{
		s = tokenz_value(lexer);
		val = ft_strjoin(val, s);
		lexer_advance(lexer);
	}
	s = my_getenv(val, env_dyalna);
	free(val);
	if (lexer->c == '$')
		s = ft_strjoin(s, expand_inside_quotes(lexer, env_dyalna));
	return (s);
}
