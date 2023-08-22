
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


// <

void	redirect_input(t_cmd  *cmd)
{
	t_redirections  *in;

	in = cmd->r_in;
	while (in)
	{
		if (in->type == IN_ID)
		{
			in->fd = open(in->file, O_RDONLY);
			if (in->fd == -1) // error
				return ;
			dup2(in->fd, STDIN_FILENO);
			close(in->fd);
			break ;
		}
		in = in->next;
	}
}

