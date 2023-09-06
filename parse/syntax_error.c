/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:30:21 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/06 17:52:13 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax(t_token **token)
{
	t_type	current;
	t_type	before;
	int		i;

	i = 0;
	before = -1;
	while (token[i])
	{
		current = token[i]->type;
		if (before != WORD_ID && i != 0 && current != WORD_ID
			&& before != PIPE_ID && current != PIPE_ID)
			return (0);
		if (i == 0 && current == PIPE_ID)
			return (0);
		before = current;
		i++;
	}
	if (current != WORD_ID)
		return (0);
	return (1);
}

int	error_msg(int flag)
{
	if (flag == 1)
		ft_putstr_fd("syntax error near unexpected token\n", 2);
	if (flag == 2)
		ft_putstr_fd("syntax error open quotes\n", 2);
	// g_exit_status = 258;
	return (0);
}
