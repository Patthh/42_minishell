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
