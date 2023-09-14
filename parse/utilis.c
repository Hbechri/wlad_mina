/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:31:35 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/13 13:10:00 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*norme_join_word(t_lexer *lexer, t_env_lst **env_dyalna)
{
	char	*s;

	s = expand_inside_quotes(lexer, env_dyalna);
	lexer_back(lexer);
	return (s);
}

char	*join_word(t_lexer *lexer, t_env_lst **env_dyalna)
{
	char	*val;
	char	*s;

	val = ft_strdup("");
	while (!if_operator(lexer->c) && !is_space(lexer->c) && lexer->c != '\0')
	{
		if (lexer->c == '\'' || lexer->c == '\"')
		{
			s = join_string(lexer, lexer->c, env_dyalna);
			val = ft_strjoin(val, s);
			free(s);
			break ;
		}
		else if (lexer->c == '$')
			s = norme_join_word(lexer, env_dyalna);
		else
			s = tokenz_value(lexer);
		val = ft_strjoin(val, s);
		free(s);
		lexer_advance(lexer);
	}
	if (val[0] == '\0')
		return ((char *)free_value(val));
	return (val);
}

t_token	*operator_type(t_lexer *lexer)
{
	if (lexer->c == '|')
		return (token_returns(lexer,
				init_tokens(tokenz_value(lexer), PIPE_ID)));
	else if (lexer->c == '<')
	{
		if (lexer->content[lexer->i + 1] == '<')
		{
			lexer_advance(lexer);
			return (token_returns(lexer,
					init_tokens(tokenz_value(lexer), HERDOC_ID)));
		}
		return (token_returns(lexer, init_tokens(tokenz_value(lexer), IN_ID)));
	}
	else if (lexer->c == '>')
	{
		if (lexer->content[lexer->i + 1] == '>')
		{
			lexer_advance(lexer);
			return (token_returns(lexer,
					init_tokens(tokenz_value(lexer), APPEND_ID)));
		}
		return (token_returns(lexer, init_tokens(tokenz_value(lexer), OUT_ID)));
	}
	return (NULL);
}

int	is_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	if_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
