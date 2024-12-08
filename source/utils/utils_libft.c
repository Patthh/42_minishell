#include "../../include/minishell.h"

// fills memory area 's' with a specified byte 'c' for 'n' bytes
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

// compares two strings
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

// duplicates the first 'n' character of 'src' into 'dest'
char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = 0;
	while (src[i] != '\0' && i < n)
		i++;
	dest = malloc(i + 1);
	if (!dest)
		return (NULL);
	while (j < i)
	{
		dest[j] = src[j];
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

// finds the first occurence of a character in a string
// returns a pointer to 'c' if found or NULL if not
char	*ft_strchr(const char *string, int c)
{
	char	target;

	target = (char)c;
	while (*string)
	{
		if (*string == target)
		{
			return ((char *)string);
		}
		string++;
	}
	if (target == '\0')
	{
		return ((char *)string);
	}
	return (NULL);
}

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}
