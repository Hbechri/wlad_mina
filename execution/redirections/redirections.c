

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

void	redirections(t_cmd *cmd)
{
	t_redirections *r_in;
	t_redirections *r_out;
	t_redirections *r_append;
	t_redirections *heredoc;

	r_in = cmd->r_in;
	r_out = cmd->r_out;
	r_append = cmd->r_append;
	heredoc = cmd->heredoc;

	while (r_in)
	{
		redirect_input(cmd, r_in);
		r_in = r_in->next;
	}
	while (r_out)
	{
		redirect_output(cmd, r_out);
		r_out = r_out->next;
	}
	while (r_append)
	{
		redirect_append(cmd, r_append);
		r_append = r_append->next;
	}
	while (heredoc)
	{
		redirect_heredoc(cmd, heredoc);
		heredoc = heredoc->next;
	}
}