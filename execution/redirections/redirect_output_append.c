/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output_append.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:38:32 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/12 15:48:10 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    redirect_output_append(t_command  *cmd)
{
    t_redirection  *append;
    int fd;

    append = cmd->redirection;
    while (append)
    {
        if (append->type == APPEND_ID)
        {
            fd = open(append->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1) // error
                return ;
            dup2(fd, STDOUT_FILENO);
            close(fd);
            break ;
        }
        append = append->next;
    }
}


// ls > $USER ==> must expand $USER to the user name
// ls > "$USER" ==> must expand $USER to the user name
// ls > '$USER' ==> must NOOOOOOT expand $USER to the user name


// int main() {
//     // Example usage of the structures and functions
    
//     // Creating a sample t_cmd structure
//     t_cmd *cmd = malloc(sizeof(t_cmd));
//     cmd->cmd = malloc(sizeof(char*) * 3);
//     cmd->cmd[0] = "ls";
//     // cmd->cmd[1] =;
//     cmd->cmd[1] = NULL;  // Command array must be NULL-terminated
    
//     // Creating and adding redirections
//     t_redirections *r_out = malloc(sizeof(t_redirections));
//     r_out->file = "output.txt";
//     r_out->fd = -1;
//     r_out->type = APPEND_ID;
//     r_out->next = NULL;
//     cmd->r_append = r_out;
    
//     // Calling redirection function
//     redirect_output_append(cmd);
    
//     // Executing the command (this is just an example, actual execution may differ)
//     execvp(cmd->cmd[0], cmd->cmd);
    
//     // Freeing memory (you should free allocated memory after usage)
//     free(r_out);
//     free(cmd->cmd);
//     free(cmd);
    
//     return 0;
// }
