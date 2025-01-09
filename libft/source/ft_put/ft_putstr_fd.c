#include "../../include/libft.h"

// writes a string to a file descriptor
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

// int main(void)
// {
// 	ft_putstr_fd("Hello, Bangkok!", 1);
// 	return (0);
// }
