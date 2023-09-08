/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:17:14 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/08 22:55:06 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ac_check(int ac)
{
	// g_exit_status = 0;
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
    t_token *token;

	(void)av;
    (void)cmd;
    (void)token;
    ac_check(ac);
    env_copy = env_dyalna(env);
    while(1)
    {
        input = readline("minishell : ");
        if(!input)
        {
            ft_putstr_fd("exit", 2);
            exit(1);
        }
        add_history(input);
        cmd = parse(input, env_copy);
		execution(cmd, env_copy);
    }
}