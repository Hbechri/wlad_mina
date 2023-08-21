
typedef struct s_redirections
{
    char *file;
    int fd;
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

void	redirect_input(t_cmd  *cmd, t_redirections *redirections)
{

}