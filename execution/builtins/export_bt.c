/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 21:35:24 by hbechri           #+#    #+#             */
/*   Updated: 2023/08/18 22:02:36 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../env/env_header.h"

void	export_bt(char **cmd, t_env_lst *env)
{
	t_env_lst	*tmp;

	tmp = env;
	if (!cmd[1])
	{
		while (tmp)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->key, 1);
			if (tmp->value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(tmp->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
			tmp = tmp->next;
		}
	}
	else
	{
		int i = 1;
		while (cmd[i])
		{
			tmp = env;
			while (tmp)
			{
				if (ft_strcmp(cmd[i], tmp->key) == 0)
				{
					ft_putstr_fd("declare -x ", 1);
					ft_putstr_fd(tmp->key, 1);
					if (tmp->value)
					{
						ft_putstr_fd("=\"", 1);
						ft_putstr_fd(tmp->value, 1);
						ft_putstr_fd("\"", 1);
					}
					ft_putstr_fd("\n", 1);
					break ;
				}
				tmp = tmp->next;
			}
			i++;
		}
	}
}

void	env_bt(t_env_lst **env_lst)
{
	t_env_lst *node;

	node = *env_lst;
	while(node)
	{
		ft_putstr_fd(node->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(node->value, 1);
		ft_putstr_fd("\n", 1);
		node = node->next;
	}
}

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


int main(int ac, char **av, char **env) {
    // Create a sample environment variables list
    (void)ac;
	(void)av;
	t_env_lst **env_lst;
	env_lst = env_dyalna(env);

	printf("Initial environment variables:\n\n");
    env_bt(env_lst);
    // Simulate command-line arguments
	printf("\nTest 1: export\n\n");
    char *testCmd1[] = { "export", "ZZZ", NULL };
    //char *testCmd2[] = { "export", "VAR1", "VAR2", NULL };
    export_bt(testCmd1, *env_lst);
    //export_bt(testCmd2, env_lst);

	free_list(env_lst);
    return 0;
}