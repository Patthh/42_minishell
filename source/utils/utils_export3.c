/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pracksaw <pracksaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:36:34 by pracksaw          #+#    #+#             */
/*   Updated: 2025/01/25 18:36:35 by pracksaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// prints exported variables value in bash format
static void	export_print_value(const char *key, const char *value)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd((char *)key, STDOUT_FILENO);
	if (value)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd((char *)value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	else if (value && *value == '\0')
	{
		ft_putstr_fd("=\"\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

// prints exported variable with or without its values
// depending on the sign and value
static void	export_print(const char *key, const char *value, int sign)
{
	if (sign)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd((char *)key, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else if (value == NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd((char *)key, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
	{
		export_print_value(key, value);
	}
}

// prints exported variables in sorted order
static void	export_print_sorted(t_env **sorted, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		export_print(sorted[i]->key, sorted[i]->value, sorted[i]->sign);
		i++;
	}
}

// prints exported variables in the environement
// sorted alphabetically
void	print_export(t_program *minishell)
{
	t_env	**sorted;
	int		size;

	sorted = export_sorting(minishell, &size);
	if (sorted)
	{
		export_print_sorted(sorted, size);
		free (sorted);
	}
	minishell->status = 0;
}
