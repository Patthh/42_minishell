/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:50:43 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:50:44 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

// write a character to a file descriptor
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// int main(void)
// {
// 	ft_putchar_fd('X', 1);
// 	printf("\n");
// 	return (0);
// }
