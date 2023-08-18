#include <unistd.h>
#include "../env/env_header.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (!str1 || !str2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (str1[i] != str2[i])
			break ;
		i++;
	}	
	if (str1[i] > str2[i])
		return (1);
	else if (str1[i] < str2[i])
		return (-1);
	return (0);
}

void	*env_search(t_env_lst **env)
{
	t_env_lst	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp("HOME", tmp->key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	pwd_and_old_pwd(t_env_lst *env, char *old_pwd, char *current_pwd)
{
	t_env_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp("OLDPWD", tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = old_pwd;
		}
		if (ft_strcmp("PWD", tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = current_pwd;
		}
		tmp = tmp->next;
	}
}

int	get_env(t_env_lst *env)
{
	char	*home;

	home = env_search(&env);
	if (!home)
	{
		ft_putstr_fd("HOME not sett\n", 2);
		g_exit_status = 1;
		return (g_exit_status);
	}
	if (chdir(home) == 0)
		g_exit_status = 0;
	else
	{
		ft_putstr_fd("HOME not set\n", 2);
		g_exit_status = 1;
		return (g_exit_status);
	}
	return (g_exit_status);
}

int	ft_cd(char **av, t_env_lst *env)
{
	char	*old_pwd;
	char	*current_pwd;
	char	*buf;
	t_env_lst	*tmp;

	tmp = env;
	buf = NULL;
	old_pwd = getcwd(buf, 0);
	free(buf);
	if (av[1] == NULL || av[1][0] == '\0')
		get_env(env);
	else if (chdir(av[1]) == 0)
	{
		current_pwd = getcwd(buf, 0);
		pwd_and_old_pwd(env, old_pwd, current_pwd);
		g_exit_status = 0;
		return (g_exit_status);
	}
	else
	{
		perror("");
		g_exit_status = 1;
	}
	return (g_exit_status);
}

int main(int ac, char **av) {
    t_env_lst *env = NULL; // Initialize your environment linked list

    // Call your functions here as needed
    // Example usage:
    //char *av[] = {"ft_cd", "builtins/haha", NULL}; // Example av array
    int result = ft_cd(av, env);
    
    if (result == 0) {
        printf("cd successful\n");
    } else {
        printf("cd failed\n");
    }

    return 0;
}