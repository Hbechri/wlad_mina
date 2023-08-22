#include <unistd.h>
#include <fcntl.h>


enum {
        WORD_ID,
        PIPE_ID,
        IN_ID,
        OUT_ID,
        SPACE_ID,
        DOUBLE_Q_ID,
        SINGLE_Q_ID,
        APPEND_ID,
        HERDOC_ID,
        EXPAND_ID,
};

typedef struct s_redirections
{
    char *file;
    int fd;
	int	type;
    struct s_redirections *next;
} t_redirections;

typedef struct s_cmd
{
	char **cmd;
	t_redirections *r_in;
	t_redirections *r_out;
	t_redirections *r_append;
	t_redirections *heredoc;
	struct s_cmd *next;
} t_cmd;

void    redirect_output(t_cmd  *cmd)
{
    t_redirections  *out;

	out = cmd->r_out;
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
