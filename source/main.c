/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:42:30 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:42:31 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_program	minishell;

	(void)argc;
	(void)argv;
	init_shell(&minishell, envp);
	run_shell(&minishell);
	free_shell(&minishell);
	return (0);
}
