
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

void	heredoc(t_cmd *cmd)
{
	t_redirections *heredoc;

	heredoc = cmd->heredoc;
	while (heredoc)
	{
		if (heredoc->type == HERDOC_ID)
		{
			heredoc->fd = open(heredoc->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (heredoc->fd == -1) // error
				return ;
			dup2(heredoc->fd, STDOUT_FILENO);
			close(heredoc->fd);
			break ;
		}
		heredoc = heredoc->next;
	}
}