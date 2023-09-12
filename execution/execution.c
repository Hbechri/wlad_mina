/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:23:13 by hbechri           #+#    #+#             */
/*   Updated: 2023/09/12 18:47:18 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int wld_mina(int *fd, int in_fd, t_command *cmd, t_env_lst *env)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        if (in_fd != -1)
        {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        if (fd[0] > 2)
            close(fd[0]);
        if (!cmd)
            return (0);
        redirections(cmd, env);
        if (bt_checker(cmd))
        {
            exec_bt(cmd, env);
            exit (0);
        }
        else
            exec_cmd(cmd->cmd, env);
    }
    return (0);
}

void	mina(void)
{
	int	wait;

	while(waitpid(-1, &wait, 0) > 0)
	{
		if (WIFEXITED(wait))
		{
			g_exit_status = WEXITSTATUS(wait);
			WEXITSTATUS(wait);
		}
	}
}

void	lonely_cmd(int *fd, int in_fd, t_command *cmd, t_env_lst *env)
{
	pid_t pid;

	if (in_fd == 0 && cmd->cmd && !cmd->redirection)
	{
		if(bt_checker(cmd))
		{
			exec_bt(cmd, env);
			g_exit_status = 0;
			return ;
		}
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (fd[1] > 2)
			close(fd[1]);
		redirections(cmd, env);
		if (cmd->cmd && bt_checker(cmd))
		{
			exec_bt(cmd, env);
			exit(0);
		}
		else
		{
			exec_cmd(cmd->cmd, env);
			exit(0);
		}
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	return ;
}

void	execution(t_command *cmd, t_env_lst **env)
{
	int	fd[2];
	int	in_fd;
	
	if(cmd)
	{
		in_fd = STDIN_FILENO;
		while(cmd->next)
		{
			pipe(fd);
			wld_mina(fd, in_fd, cmd, *env);
			close(fd[1]);
			if (in_fd != STDIN_FILENO)
				close(in_fd);
			if (fd[1] > 2)
				close(fd[1]);
			in_fd = fd[0];
			cmd = cmd->next;
		}
		lonely_cmd(fd, in_fd, cmd, *env);
		mina();
	}
}
