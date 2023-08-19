/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 21:35:24 by hbechri           #+#    #+#             */
/*   Updated: 2023/08/19 21:45:15 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../env/env_header.h"

int	non_numeric(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return(1);
	return(0);
}

int	alphanum_c(char c)
{
	if (non_numeric(c) == 1)
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}


char *keyword(char *cmd)
{
	int i;
	char *key;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	key = ft_substr(cmd, 0, i);
	return (key);
}

char *value(char *cmd)
{
	int i;
	char *value;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	value = ft_substr(cmd, i + 1, ft_strlen(cmd));
	return (value);
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

int	is_separator(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

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
			if (tmp->value && tmp->value[0] != '\0')
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
		int flag = 0;
		char *key;
		char *val;
		int i = 1;
		while (cmd[i])
		{
			key = keyword(cmd[i]);
			val = value(cmd[i]);
			tmp = env;
			while (tmp)
			{
				if ((non_numeric(key[0]) == 1) && (alphanum_c(key[1])))
				{
					if(val == NULL)
						ft_lstadd_back(&tmp, ft_lstnew(key, NULL));
					else if (val)
						ft_lstadd_back(&tmp, ft_lstnew(key, val));
					break ;
				}
				else
				{
					ft_putstr_fd("export: `", 2);
					ft_putstr_fd(key, 2);
					ft_putstr_fd("': not a valid identifier\n", 2);
					break ;
				}
				tmp = tmp->next;
			}
			i++;
		}
	}
}

int main(int ac, char **av, char **env) {
    // Create a sample environment variables list
    (void)ac;
	(void)av;
	t_env_lst **env_lst;
	env_lst = env_dyalna(env);
	
	printf("\nTest 1: export\n\n");
    char *testCmd1[] = { "export","y4==", NULL };
    export_bt(testCmd1, *env_lst);

	printf("Initial export variables:\n\n");
    char *testCmd2[] = { "export", NULL };
	export_bt(testCmd2, *env_lst);
    // Simulate command-line arguments
    //char *testCmd2[] = { "export", "VAR1", "VAR2", NULL };
    //export_bt(testCmd2, env_lst);

	free_list(env_lst);
    return 0;
}