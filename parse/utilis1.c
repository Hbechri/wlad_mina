/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:18:23 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/13 18:25:26 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*after_quotes(t_lexer *lexer, char *val, t_env_lst **env_dyalna)
{
	char	*s;
	char	*tmp;

	if (lexer->c == '\'' || lexer->c == '\"')
	{
		s = join_string(lexer, lexer->c, env_dyalna);
		tmp = ft_strjoin(val, s);
		free(s);
		return (tmp);
	}
	else
	{
		s = join_word(lexer, env_dyalna);
		tmp = ft_strjoin(val, s);
		free(s);
		return (tmp);
	}
}

char	*join_string(t_lexer *lexer, char c, t_env_lst **env_dyalna)
{
	char		*val;
	char		*s;

	val = ft_strdup("");
	lexer_advance(lexer);
	while (lexer->c != c && lexer->c != '\0')
	{
		if (lexer->c == '$' && c == '\"')
		{
			s = expand_inside_quotes(lexer, env_dyalna);
			lexer_back(lexer);
		}
		else
			s = tokenz_value(lexer);
		val = ft_strjoin(val, s);
		free(s);
		lexer_advance(lexer);
	}
	if (lexer->c != c)
		error_quotes_join(lexer);
	lexer_advance(lexer);
	if (!if_operator(lexer->c) && !is_space(lexer->c) && lexer->c != '\0')
		val = after_quotes(lexer, val, env_dyalna);
	return (val);
}

t_token	*word_type_colect(t_lexer *lexer, t_env_lst **env_dyalna)
{
	char	*val;
	char	*s;

	val = ft_strdup("");
	while (!if_operator(lexer->c) && !is_space(lexer->c) && lexer->c != '\0')
	{
		if (lexer->c == '\'' || lexer->c == '\"')
		{
			lexer->must_not_expand = 1;
			s = join_string(lexer, lexer->c, env_dyalna);
			val = ft_strjoin(val, s);
			free(s);
			break ;
		}
		else if (lexer->c == '$')
			s = norme_word_type_collect(lexer, env_dyalna);
		else
			s = tokenz_value(lexer);
		val = ft_strjoin(val, s);
		free(s);
		lexer_advance(lexer);
	}
	if (val[0] == '\0')
		return (free_value(val));
	return (init_tokens(val, WORD_ID));
}

t_token	*error_quotes(char *val, t_lexer *lexer)
{
	lexer->error = 1;
	free(val);
	g_exit_status = 1;
	return (NULL);
}

t_token	*string_type_collect(t_lexer *lexer, char c, t_env_lst **env_dyalna)
{
	char	*val;
	char	*s;

	val = ft_strdup("");
	lexer_advance(lexer);
	while (lexer->c != c && lexer->c != '\0')
	{
		if (lexer->c == '$' && c == '\"')
		{
			s = expand_inside_quotes(lexer, env_dyalna);
			lexer_back(lexer);
		}
		else
			s = tokenz_value(lexer);
		val = ft_strjoin(val, s);
		free(s);
		lexer_advance(lexer);
	}
	if (lexer->c != c)
		return (error_quotes(val, lexer));
	lexer_advance(lexer);
	if (!if_operator(lexer->c) && !is_space(lexer->c) && lexer->c != '\0')
		val = after_quotes(lexer, val, env_dyalna);
	return (init_tokens(val, WORD_ID));
}
