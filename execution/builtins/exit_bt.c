/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:34:47 by hbechri           #+#    #+#             */
/*   Updated: 2023/08/18 18:34:48 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../../libft/libft.h"

int	exit_bt(char	**cmd)
{
	int	i;
	int j = 0;
	int num = 0;
	i = 0;
	while (cmd[i])
		i++;
	if (i == 1)
		exit(0);
	else if (i == 2)
	{
		while (cmd[1][j])
		{
			if (ft_isdigit(cmd[1][j]) == 0)
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(cmd[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(255);
			}
			j++;
		}
		if (ft_isdigit(cmd[1][0]) == 1)
			exit(ft_atoi(cmd[1]));
		else
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
	else
	{
		int flag = 0;
		i = 1;
		j = 0;
		while(cmd[i])
		{
			while (cmd[i][j])
			{
				if (ft_isdigit(cmd[i][j]) == 1)
					num++;
				j++;
			}
			if(num == j)
				flag += 1;
			j = 0;
			num = 0;
			i++;
		}
		if (flag == (i - 1))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		else
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For string functions
// Include other necessary header files

int main() {
    char input[100];
    char *cmd[10]; // Adjust the size as needed

    while (1) {
        printf("Enter a command: ");
        fgets(input, sizeof(input), stdin);

        // Tokenize input into cmd array
        int i = 0;
        char *token = strtok(input, " \t\n");
        while (token != NULL) {
            cmd[i++] = token;
            token = strtok(NULL, " \t\n");
        }
        cmd[i] = NULL; // Null-terminate the array

        if (i > 0) {
            if (strcmp(cmd[0], "exit") == 0) {
                exit_bt(cmd); // Call your exit_bt function here
                //break; // Exit the loop
            } else {
                // Handle other commands or perform other tasks
                printf("Command not recognized.\n");
            }
        }
    }

    return 0;
}
