#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*temp;
	unsigned char	*end;

	temp = (unsigned char *)s;
	end = temp + n;
	while (temp < end)
		*temp++ = c;
	return (s);
}


int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char	*line;
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, "exit") == 0)
		{
			free (line);
			break ;
		}
		printf(PROMPT);
		printf("%s\n", line);
		free (line);
	}
	return (0);
}
