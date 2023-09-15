/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:08:29 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/15 02:46:41 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include <sys/wait.h>
# include <dirent.h>

extern int	g_exit_status;

typedef struct s_lexer
{
	char			*content;
	int				must_not_expand;
	int				size;
	char			c;
	int				i;
	int				error;
}				t_lexer;

typedef enum e_excode
{
	EX_SUCCESS = 0,
	EX_FAILURE = 1,
	EX_BT_FAIL = 2,
	EX_CNOT_EXEC = 126,
	EX_CNOT_FIND = 127,
	EX_BY_SIGNAL = 128,
	EX_OUTOF_RANGE = 255
}	t_excode;

typedef enum e_type
{
	WORD_ID,
	PIPE_ID,
	IN_ID,
	OUT_ID,
	APPEND_ID,
	HERDOC_ID,
}			t_type;

typedef struct s_token
{
	char	*value;
	t_type	type;
}			t_token;

typedef struct s_redirection
{
	int						type;
	char					*file;
	char					*hdc_file;
	struct s_redirection	*next;
}						t_redirection;

typedef struct s_env_lst
{
	char				*key;
	char				*value;
	struct s_env_lst	*next;
}					t_env_lst;

typedef struct s_command
{
	char				**cmd;
	int					dlm;
	t_type				type;
	t_env_lst			*envp;
	t_redirection		*redirection;
	struct s_command	*next;
}				t_command;

//libft_utilis
char			*ft_strjoin3(char *s1, char *s2, char *s3);
char			*ft_strjoin_unfreeable(char *s1, char *s2);
void			delete_node(t_env_lst *node);
void			free_list(t_env_lst **env_lst);
void			ft_lstadd_back(t_env_lst **list, t_env_lst *new);
void			ft_lstadd_back(t_env_lst **list, t_env_lst *new);
t_env_lst		*ft_lstnew(char *keyword, char *value);
int				ft_strcmp(char *s1, char *s2);
int				ft_lstsize(t_env_lst *lst);
char			*ft_strcpy(char *dst, const char *src);
//parse
t_env_lst		**env_dyalna(char **env);
t_env_lst		*our_getenv(char *key, t_env_lst **env_dyalna);
char			*my_getenv(char *key, t_env_lst **env_dyalna);
char			*expand_exit(t_lexer *lexer);
char			*expandcheck(t_lexer *lexer, char *s, t_env_lst **env_dyalna);
char			*expand_inside_word(t_lexer *lexer, t_env_lst **env_dyalna);
char			*expand_inside_quotes(t_lexer *lexer, t_env_lst **env_dyalna);
t_lexer			*init_lexer(char *content);
void			lexer_advance(t_lexer *lexer);
void			lexer_back(t_lexer *lexer);
t_token			*lexer_next_token(t_lexer *lexer, t_env_lst **env_dyalna);
void			lexer_skip_white_spaces(t_lexer *lexer);
char			**command_allocation(char **curr, char *cmd);
void			init(t_token **token, t_command *cmd, int i);
t_command		*init_commands(void);
t_command		*create_cmd(t_token **token, t_command *cmd);
t_command		*parse(char *line, t_env_lst **env_dyalna);
t_redirection	*init_redirection(char *val, t_type type);
void			new_redirecion(t_redirection *head, char *val, t_type type);
int				check_syntax(t_token **token);
int				error_msg(int flag);
t_token			*init_tokens(char *value, t_type type);
char			*tokenz_value(t_lexer *lexer);
t_token			*token_returns(t_lexer *lexer, t_token *token);
int				token_array_lenght(t_token **token);
t_token			**new_token(t_token **curr, t_token *token);
void			token_free(t_token **token);
t_token			*free_value(char *val);
char			*join_word(t_lexer *lexer, t_env_lst **env_dyalna);
t_token			*operator_type(t_lexer *lexer);
int				is_space(int c);
int				if_operator(char c);
char			*after_quotes(t_lexer *lexer, char *val,
					t_env_lst **env_dyalna);
char			*join_string(t_lexer *lexer, char c, t_env_lst **env_dyalna);
t_token			*word_type_colect(t_lexer *lexer, t_env_lst **env_dyalna);
t_token			*error_quotes(char *val, t_lexer *lexer);
t_token			*string_type_collect(t_lexer *lexer, char c,
					t_env_lst **env_dyalna);
int				array_len(char **array);
int				if_special_char(char c);
t_token			*error_quotes_join(t_lexer *lexer);
char			*norme_word_type_collect(t_lexer *lexer,
					t_env_lst **env_dyalna);
t_token			*free_value(char *val);
void			free_redirections(t_redirection *rdr);
void			free_env_lst(t_env_lst *env_lst);
void			free_cmd(t_command *cmd);

//execution
void			cd_error(char *cmd, char *old_pwd);
int				is_alpha_and_underscore(char c);
char			*dollar_word(char *str);
char			*replace_with_value(char *line, char *word, t_env_lst **env);
char			*expand_in_hdc(char *exp, t_env_lst **env);
char			*remove_quotes(char *str);
int				non_numeric(char c);
char			*value(char *cmd);
char			*keyword(char *cmd);
int				alpha_and_underscore(char *key);
int				is_valid_key(t_env_lst *env, char *key, char *val);
void			export_error(char *key, char *val);
void			no_such_file(char *cmd);
void			cmd_not_found(char *cmd);
void			is_directory(char *cmd, DIR *dir);
int				valid_cmd(char *cmd);
char			**env_table(t_env_lst *env);
void			just_dup(int fd, int std);
int				cd_bt(char **av, t_env_lst *env);
int				echo_bt(char **cmd);
void			env_bt(t_env_lst *env_lst);
int				exit_bt(char	**cmd);
void			export_bt(char **cmd, t_env_lst *env);
int				pwd_bt(void);
void			unset_bt(char **cmd, t_env_lst *env);
int				bt_checker(t_command *cmd);
void			exec_bt(t_command *cmd, t_env_lst *env);
void			lonely_cmd(int *fd, int in_fd, t_command *cmd, t_env_lst *env);
void			mina(void);
int				wld_mina(int *fd, int in_fd, t_command *cmd, t_env_lst *env);
void			execution(t_command *cmd, t_env_lst **env);
void			exec_cmd(char **cmd, t_env_lst *env);
void			heredoc(t_command *cmd, t_env_lst *env);
void			redirect_input(t_command *cmd);
void			redirect_output_append(t_command *cmd);
void			redirect_output(t_command *cmd);
void			redirections(t_command *cmd);
char			*heredoc_file_name(void);
char			*ignore_spaces(char *str);
void			heredoc_boucle(char *delimiter, int fd,
					t_env_lst **env, t_command *cmd);
char			*set_delimiter(t_redirection *heredoc);
void			pid_error(void);
void			heredoc_setup(t_command *cmd,
					t_env_lst *env, t_redirection *heredoc);
#endif