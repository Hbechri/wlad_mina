/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:38:05 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/08 15:38:07 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    redirect_output(t_command  *cmd)
{
    t_redirection  *out;

	out = cmd->redirection;
	while (out)
	{
		if (out->type == OUT_ID)
		{
			out->fd = open(out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (out->fd == -1) // error
				return ;
			dup2(out->fd, STDOUT_FILENO);
			close(out->fd);
			break ;
		}
		out = out->next;
	}
}

// ls > $USER ==> must expand $USER to the user name
// ls > "$USER" ==> must expand $USER to the user name
// ls > '$USER' ==> must NOOOOOOT expand $USER to the user name

// #include <unistd.h>
// #include <fcntl.h>
// #include <stdlib.h>  // For malloc, free

// int main() {
//     // Example usage of the structures and functions
    
//     // Creating a sample t_cmd structure
//     t_cmd *cmd = malloc(sizeof(t_cmd));
//     cmd->cmd = malloc(sizeof(char*) * 3);
//     cmd->cmd[0] = "ls";
//     cmd->cmd[1] = "-la";
//     cmd->cmd[2] = NULL;  // Command array must be NULL-terminated
    
//     // Creating and adding redirections
//     t_redirections *out = malloc(sizeof(t_redirections));
//     out->file = "output1.txt";
//     out->fd = -1;
//     out->type = OUT_ID;
//     out->next = NULL;
//     cmd->r_out = out;
    
//     // Calling redirection function
//     redirect_output(cmd);
    
//     // Executing the command (this is just an example, actual execution may differ)
//     execvp(cmd->cmd[0], cmd->cmd);
    
//     // Freeing memory (you should free allocated memory after usage)
//     free(out);
//     free(cmd->cmd);
//     free(cmd);
    
//     return 0;
// }
