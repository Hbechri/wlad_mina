typedef struct s_env_lst
{
    char *key;
    char *value;
    struct s_env_lst *next;
} t_env_lst;

#include "../../libft/libft.h"
#include <stdio.h>




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

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	t_env_lst **env_lst;
// 	env_lst = env_dyalna(env);
// 	env_bt(env_lst);
// 	free_list(env_lst);
// 	return (0);
// }