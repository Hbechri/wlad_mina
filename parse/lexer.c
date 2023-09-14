/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:51:46 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/13 18:09:16 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*init_lexer(char *content)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->content = content;
	lexer->size = ft_strlen(content);
	lexer->i = 0;
	lexer->error = 0;
	lexer->must_not_expand = 0;
	lexer->c = content[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->i < lexer->size && lexer->c)
	{
		lexer->i += 1;
		lexer->c = lexer->content[lexer->i];
	}
}

void	lexer_back(t_lexer *lexer)
{
	if (lexer->i > 0)
	{
		lexer->i--;
		lexer->c = lexer->content[lexer->i];
	}
}

t_token	*lexer_next_token(t_lexer *lexer, t_env_lst **env_dyalna)
{
	while (lexer->c != '\0' && lexer->i < lexer->size)
	{
		if (is_space(lexer->c))
			lexer_skip_white_spaces(lexer);
		if (!if_operator(lexer->c) && lexer->c != '\'' && lexer->c != '\"')
			return (word_type_colect(lexer, env_dyalna));
		if (lexer->c == '\"')
		{
			lexer->must_not_expand = 1;
			return (string_type_collect(lexer, lexer->c, env_dyalna));
		}
		if (lexer->c == '\'')
		{
			lexer->must_not_expand = 1;
			return (string_type_collect(lexer, lexer->c, env_dyalna));
		}
		return (operator_type(lexer));
	}
	return (NULL);
}

void	lexer_skip_white_spaces(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t' || lexer->c == '\n'
		|| lexer->c == '\v' || lexer->c == '\f' || lexer->c == '\r')
		lexer_advance(lexer);
}
