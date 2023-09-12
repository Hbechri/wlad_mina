/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:17:14 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/12 15:38:42 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	sig_int_handler()
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_handler);
}

void	ac_check(int ac)
{
	g_exit_status = 0;
	if (ac != 1)
	{
		write(2, "minishell : ", 13);
		write(2, "no such file or directory\n", 27);
		exit(1);
	}
}

int main(int ac, char **av, char **env)
{
    char *input;
    t_env_lst   **env_copy;
    t_command   *cmd;

	(void)av;
    cmd = NULL;
    ac_check(ac);
    env_copy = env_dyalna(env);
    set_signals();
    while(1)
    {
        input = readline("minishell : ");
        if(!input)
        {
            ft_putstr_fd("exit", 2);
            exit(1);
        }
        if (ft_isprint(input[0]))
            add_history(input);
        cmd = parse(input, env_copy);
		execution(cmd, env_copy);
    }
}