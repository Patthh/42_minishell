/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:44:17 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:44:18 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// echo -n
// echo -n -n
// echo -n -n -n hello              is valid
// skips all -n flags
// cc ft_echo.c ../utils/utils_libft.c
// run ./a.out -n argument
// flag -n do not output the trailing newline

static int	case_empty(t_program *minishell)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	minishell->status = 0;
	return (0);
}

static int	flag_valid(const char *argument)
{
	int	i;

	if (!argument || argument[0] != '-' || argument[1] != 'n')
		return (0);
	i = 2;
	while (argument[i])
	{
		if (argument[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	echo_flag(char **arguments, int *i)
{
	int	new_line;
	int	valid;

	new_line = 0;
	valid = 0;
	while (arguments[*i])
	{
		if (!valid && flag_valid(arguments[*i]))
		{
			new_line = 1;
			(*i)++;
		}
		else
		{
			valid = 1;
			break ;
		}
	}
	return (new_line);
}

static void	echo_print(char **arguments, int start)
{
	int	i;

	i = start;
	while (arguments[i])
	{
		ft_putstr_fd(arguments[i], STDOUT_FILENO);
		if (arguments[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
}

int	ft_echo(t_command *command, t_program *minishell)
{
	int	i;
	int	new_line;

	i = 1;
	if (!command->arguments[i])
		return (case_empty(minishell));
	new_line = echo_flag(command->arguments, &i);
	echo_print(command->arguments, i);
	if (!new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	minishell->status = 0;
	return (0);
}

// FOR TESTING
// cc -Wall -Werror -Wextra ft_echo.c ../../libft/libft.a
// int main(int argc, char **argv)
// {
// 	t_command	command;
// 	t_program	minishell;

// 	(void)argc;
// 	command.arguments = argv;

// 	ft_echo(&command, &minishell);
// 	// printf("Exit status: %d\n", minishell.status);
// 	return (0);
// }
