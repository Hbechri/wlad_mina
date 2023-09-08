/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:31:16 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/08 16:34:56 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_lst	**env_dyalna(char **env)
{
	t_env_lst	**env_lst;
	t_env_lst	*node;
	int			i;
	char		*key;
	char		*value;

	env_lst = ft_calloc(1, sizeof(t_env_lst *));
	i = 0;
	while (env[i])
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

t_env_lst	*our_getenv(char *key, t_env_lst **env_dyalna)
{
	t_env_lst	*current;

	if (!key)
		return (NULL);
	current = (*env_dyalna);
	while (current->next != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	if (ft_strcmp(current->key, key) == 0)
		return (current);
	return (NULL);
}

char	*my_getenv(char *key, t_env_lst **env_dyalna)
{
	t_env_lst	*new;

	new = our_getenv(key, env_dyalna);
	if (new != NULL)
		return (ft_strdup(new->value));
	else
		return (ft_strdup(""));
}
