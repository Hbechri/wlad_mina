/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:23:09 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/10 17:57:26 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*init_tokens(char *value, t_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = value;
	token->type = type;
	return (token);
}

char	*tokenz_value(t_lexer *lexer)
{
	char	*token;

	token = malloc(sizeof(char) * 2);
	token[0] = lexer->c;
	token[1] = '\0';
	return (token);
}

t_token	*token_returns(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

t_token	**new_token(t_token **curr, t_token *token)
{
	t_token		**new;
	int			l;
	int			i;

	l = token_array_lenght(curr);
	i = 0;
	new = (t_token **)malloc(sizeof(t_token *) * (l + 2));
	while (i < l)
	{
		new[i] = (curr[i]);
		i++;
	}
	free(curr);
	new[i++] = token;
	new[i] = NULL;
	return (new);
}

void	token_free(t_token **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		free(token[i]->value);
		free(token[i]);
		i++;
	}
	free(token);
}
