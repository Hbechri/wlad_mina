#include "../../libft/libft.h"
#include "../env/env_header.h"
#include <sys/types.h>


void	ft_lstadd_back(t_env_lst **list, t_env_lst *new)
{
	t_env_lst	*ptr;

	if (list == NULL)
		return ;
	else if (*list == NULL)
		*list = new;
	else
	{
		ptr = *list;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

t_env_lst	*ft_lstnew(char *keyword ,char *value)
{
	t_env_lst	*list;

	list = (t_env_lst *)malloc((sizeof(t_env_lst)));
	if (list == NULL)
		return (NULL);
	list->key = ft_strdup(keyword);
	list->value = ft_strdup(value);
	list->next = NULL;
	return (list);
}

void	delete_node(t_env_lst *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

void free_list(t_env_lst **env_lst)
{
	t_env_lst *tmp;
	t_env_lst *node;

	node = *env_lst;
	while(node)
	{
		tmp = node->next;
		delete_node(node);
		node = tmp;
	}
	free(env_lst);
}

t_env_lst	**env_dyalna(char **env)
{
	int i;
	t_env_lst **env_lst;
	t_env_lst *node;
	char *key;
	char *value;

	env_lst = ft_calloc(1, sizeof(t_env_lst *));
	i = 0;
	while(env[i])
	{
		key = ft_strchr(env[i], '=');
		value = ft_strchr(env[i], '=');
		key = ft_substr(env[i], 0, key - env[i]);
		value = ft_substr(env[i], value - env[i] + 1, ft_strlen(env[i]));
		node = ft_lstnew(key, value);
		ft_lstadd_back(env_lst, node);
		free(key);
		free(value);
		i++;
	}
	return (env_lst);
}


int	ft_lstsize(t_env_lst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return(i);
}

void	exec_cmd(char **cmd, t_env_lst *env)
{
	char	**envp;
	char 	*path;
	char 	**splitted_paths;
	char	*tmp_path;
	int		i;

	i = 0;
	envp = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	while (env)
	{
		envp[i] = ft_strjoin(env->key, "=");
		envp[i] = ft_strjoin(envp[i], env->value);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	i = 0;
	if (cmd == NULL)
		return ;
	else
	{
		while(envp[i])
		{
			if (ft_strnstr(envp[i], "PATH", 4))
			{
				path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
				//printf("%s\n", path);
				break ;
			}
			i++;
		}
		if (path)
		{
			splitted_paths = ft_split(path + 5, ':');
			i = 0;
			while (splitted_paths[i])
			{
				tmp_path = ft_strjoin(splitted_paths[i], "/");
				tmp_path = ft_strjoin(tmp_path, cmd[0]);
				//printf("%s\n", tmp_path);
				if (access(tmp_path, F_OK) == 0)
				{
					execve(tmp_path, cmd, envp);
					break ;
				}
				i++;
			}
		}
	}
}

int main(int ac,char **av, char **env) {
	(void)ac;
	(void)av;
	t_env_lst **env_lst;
	env_lst = env_dyalna(env);

    char *command[] = {"cat" , NULL};  // Example command
    exec_cmd(command, *env_lst);

    return 0;
}