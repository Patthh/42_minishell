/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:44:18 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:44:19 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_env(t_program *minishell)
{
	int		i;
	char	*key;
	char	*value;
	char	*sign;

	minishell->env_list = NULL;
	minishell->env_len = 0;
	i = 0;
	while (minishell->envp[i])
	{
		sign = ft_strchr(minishell->envp[i], '=');
		if (sign)
		{
			key = ft_strndup(minishell->envp[i], sign - minishell->envp[i]);
			value = ft_strdup(sign + 1);
			add_env(minishell, key, value, 0);
			free(key);
			free(value);
		}
		i++;
	}
	minishell->envp = NULL;
}

char *ft_multjoin(char **arr_str)
{
	char	*res;
	char	*tmp;

	if (!arr_str && !*arr_str)
		return (NULL);
	res = ft_strdup(*arr_str++);
	while (*arr_str)
	{
		tmp = ft_strjoin(res, *arr_str);
		free(res);
		res = tmp;
		arr_str++;
	}
	return (tmp);
}

void	gen_env(t_program *minishell)
{
	t_env	*tmp;
	size_t	i;

	if (minishell->envp != NULL)
		free_environ(minishell->envp);
	i = 0;
	minishell->envp = malloc(sizeof(*minishell->envp) * (minishell->env_len + 1));
	tmp = minishell->env_list;
	while (tmp)
	{
		minishell->envp[i++] = ft_multjoin((char *[]){tmp->key, "=", tmp->value, NULL});
		tmp = tmp->next;
	}
	minishell->envp[i] = NULL;
}

void	add_env(t_program *minishell, const char *key, const char *value,
			int sign)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->sign = sign;
	new->next = minishell->env_list;
	minishell->env_list = new;
	minishell->env_len++;
}

void	free_env(t_program *minishell)
{
	t_env	*temp;

	while (minishell->env_list)
	{
		temp = minishell->env_list;
		minishell->env_list = minishell->env_list->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	free_environ(minishell->envp);
}

t_env	*env_find(t_env *env_list, const char *key)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	ft_env(t_program *minishell)
{
	t_env	*current;

	current = minishell->env_list;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	minishell->status = 0;
	return (0);
}
