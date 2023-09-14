/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:38:13 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/13 13:07:45 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	array_len(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
			i++;
	}
	return (i);
}

int	token_array_lenght(t_token **token)
{
	int	i;

	i = 0;
	if (token)
	{
		while (token[i] != NULL)
			i++;
	}
	return (i);
}

int	if_special_char(char c)
{
	if (c == '!' || c == '=' || c == ',' || c == ';' || c == '<' || c == '>'
		|| c == '|' || c == '&' || c == '(' || c == ')' || c == '{'
		|| c == '}' || c == '[' || c == ']' || c == '\\' || c == '@'
		|| c == '#' || c == '~' || c == '*' || c == '^' || c == '%'
		|| c == '`' || c == '?' || c == '.' || c == ':' || c == '+' || c == '-'
		|| c == '/')
		return (1);
	return (0);
}

t_token	*error_quotes_join(t_lexer *lexer)
{
	lexer->error = 1;
	ft_putstr_fd("error\n", 2);
	return (NULL);
}

char	*norme_word_type_collect(t_lexer *lexer, t_env_lst **env_dyalna)
{
	char	*s;

	s = expand_inside_word(lexer, env_dyalna);
	lexer_back(lexer);
	return (s);
}
