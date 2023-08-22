#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>
//#include "../../get_next_line/get_next_line.h"
#include "../../libft/libft.h"

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


int	is_single_or_double_quote(char *str, int i)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}


void	heredoc(t_cmd *cmd)
{
	t_redirections *heredoc;
	char *line;
	char *delimiter;

	heredoc = cmd->heredoc;
	while (heredoc)
	{
		if (heredoc->type == HERDOC_ID)
		{
			heredoc->fd = open(heredoc->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			delimiter = heredoc->file;
			delimiter = ft_strtrim(delimiter, " ");
			while (1)
			{
				line = readline("> ");
				if (!line)
					break ;
				if (ft_strcmp(line, delimiter) == 0)
					break ;
				
				write(heredoc->fd, line, ft_strlen(line));
				write(heredoc->fd, "\n", 1);
				free(line);
			}
			close(heredoc->fd);
		}
		heredoc = heredoc->next;
	}
}


// if << '$USER' == should not expand
// if << $USER == should expand
// if << "$USER" == should not expand



int main() {
    // Create and initialize t_cmd and t_redirections structs
    t_cmd *command = (t_cmd *)malloc(sizeof(t_cmd));
    command->heredoc = (t_redirections *)malloc(sizeof(t_redirections));
    command->heredoc->file = "    example.txt"; // Replace with your desired file name
    command->heredoc->type = HERDOC_ID;
    command->heredoc->next = NULL;

    // Call heredoc function
    heredoc(command);

    // Clean up allocated memory
    free(command->heredoc);
    free(command);

    return 0;
}