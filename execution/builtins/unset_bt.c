/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:34:20 by hbechri           #+#    #+#             */
/*   Updated: 2023/08/18 21:44:04 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env_header.h"
#include "../../libft/libft.h"

void	unset_bt(char **cmd, t_env_lst *env)
{
	int		i;
	t_env_lst	*tmp;
	t_env_lst	*prev;

	i = 1;
	//hundle the non alphanumeric case and '_'
	while (cmd[i])
	{
		tmp = env;
		prev = NULL;
		while (tmp)
		{
			if (ft_strcmp(cmd[i], tmp->key) == 0)
			{
				if (prev)
					prev->next = tmp->next;
				else
					env = tmp->next;
				free(tmp->key);
				free(tmp->value);
				free(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}

int main(int ac, char **av, char **env) {
    // Create a sample environment variables list
    // Populate env with some environment variables

	(void)ac;
	(void)av;
	t_env_lst **env_lst;
	env_lst = env_dyalna(env);

    // Display the initial environment variables
    printf("Initial environment variables:\n\n");
	env_bt(env_lst);

    // Simulate command-line arguments
    char *testCmd[] = { "unset", "hfvbks", "jfvlf" , "_",NULL };
    unset_bt(testCmd, *env_lst);

    // Display the environment variables after unset
    printf("\nEnvironment variables after unset:\n\n");
	env_bt(env_lst);

    // Clean up memory (free the env list)
	free_list(env_lst);

    return 0;
}