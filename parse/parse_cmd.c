/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:25:40 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/13 17:27:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**command_allocation(char **curr, char *cmd)
{
	char	**new_cmd;
	int		l;
	int		i;

	if (cmd[0] == ' ' && cmd[1] == '\0')
		return (curr);
	l = array_len(curr);
	i = 0;
	new_cmd = malloc(sizeof(char *) * (l + 2));
	while (i < l)
	{
		new_cmd[i] = (curr[i]);
		i++;
	}
	free(curr);
	new_cmd[i++] = ft_strdup(cmd);
	new_cmd[i] = NULL;
	return (new_cmd);
}

void	init(t_token **token, t_command *cmd, int i)
{
	if (token[i]->type == WORD_ID)
	{
		cmd->cmd = command_allocation(cmd->cmd, token[i]->value);
		cmd->type = token[i]->type;
	}
	else if (token[i]->type == IN_ID || token[i]->type == OUT_ID
		|| token[i]->type == APPEND_ID || token[i]->type == HERDOC_ID)
	{
		if (cmd->redirection == NULL)
			cmd->redirection = init_redirection(token[i + 1]->value,
					token[i]->type);
		else
			new_redirecion(cmd->redirection, token[i + 1]->value,
				token[i]->type);
		cmd->type = token[i]->type;
	}
}

t_command	*init_commands(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	cmd->cmd = NULL;
	cmd->dlm = 0;
	cmd->redirection = NULL;
	cmd->envp = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_command	*create_cmd(t_token **token, t_command *cmd)
{
	t_command	*tmp;
	int			i;

	cmd = NULL;
	cmd = init_commands();
	tmp = cmd;
	i = 0;
	while (token[i])
	{
		init(token, cmd, i);
		if (token[i]->type == IN_ID || token[i]->type == OUT_ID
			|| token[i]->type == HERDOC_ID || token[i]->type == APPEND_ID)
			i++;
		if (token[i]->type == PIPE_ID)
		{
			cmd->next = init_commands();
			cmd = cmd->next;
		}
		i++;
	}
	return (tmp);
}

t_command	*parse(char *line, t_env_lst **env_dyalna)
{
	t_lexer		*lexer;
	t_token		**token;
	t_command	*cmd;
	int			i;

	cmd = NULL;
	lexer = init_lexer(line);
	token = malloc(sizeof(t_token *) * 2);
	i = 0;
	token[0] = lexer_next_token(lexer, env_dyalna);
	token[1] = NULL;
	while (token[i++])
		token = new_token(token, lexer_next_token(lexer, env_dyalna));
	if (!check_syntax(token))
		error_msg(1);
	else if (lexer->error == 1)
		error_msg(2);
	else
		cmd = create_cmd(token, cmd);
	cmd->dlm = lexer->must_not_expand;
	token_free(token);
	free(lexer);
	return (cmd);
}
