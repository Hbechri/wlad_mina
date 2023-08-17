#include <stdio.h>
#include <stdlib.h>  // For memory allocation
#include <string.h> 
#include<unistd.h>


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

int ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return(i);
}

void ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void ft_putstr_fd(char *str, int fd)
{
	int i = 0;
	while(str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	option_checker(char *cmd, char option)
{
	int	i;

	i = 2;
	if (cmd[0] != '-' || ft_strlen(cmd) < 2)
		return (EX_SUCCESS);
	while (cmd[i])
	{
		if (cmd[i] != option)
			return (EX_SUCCESS);
		i++;
	}
	return (EX_BT_FAIL);
}

int echo(char **cmd)
{
	int		i;
	int		nl_flag;

	nl_flag = 1;
	i = 1;
	while (cmd[i] && option_checker(cmd[i], 'n'))
	{
		nl_flag = 0;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1] == NULL)
			break ;
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (nl_flag == 1)
		printf("\n");
	return (EX_SUCCESS);
}



// ... (struct definitions and echo function as provided)

int main()
{
    // Create an example command array
    char *cmd[] = {"echo", NULL};

    // Allocate memory for an example environment list
    // t_list envp_list;
    // envp_list.size = 0;
    // envp_list.head = NULL;
    // envp_list.tail = NULL;
	

    // Call the echo function
    int result = echo(cmd);

    // Check the result
    // if (result == EX_SUCCESS)
    // {
    //     printf("Echo executed successfully.\n");
    // }
    // else
    // {
    //     printf("Echo execution failed.\n");
    // }

    // Clean up any allocated memory or resources if needed

    return 0;
}