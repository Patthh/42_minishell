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

	if (!s1 || !s2)
		return (-1);
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
	if (!src)
		return (NULL);
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

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dest;

	i = ft_strlen(s);
	dest = malloc(i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

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

static size_t	ft_intlen(int n)
{
	size_t	length;

	length = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		length++;
	while (n != 0)
	{
		length++;
		n /= 10;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	size_t	length;
	char	*string;
	long	number;

	length = ft_intlen(n);
	string = (char *)malloc(length + 1);
	if (!string)
		return (NULL);
	string[length] = '\0';
	number = n;
	if (number < 0)
	{
		string[0] = '-';
		number = -number;
	}
	if (number == 0)
		string[0] = '0';
	while (number)
	{
		string[--length] = (number % 10) + '0';
		number /= 10;
	}
	return (string);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	return (0);
}

int	ft_isalpha(int c)

{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*s3;

	if (!s1 && !s2)
		return (NULL);
	s3 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	return (s3);
}

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] != '\0')
		{
			j++;
		}
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}

static int	ft_length_word(const char *s, char c)
{
	int	length;
	int	i;

	length = 0;
	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		length++;
		i++;
	}
	return (length);
}

static int	ft_count_words(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
			{
				i++;
			}
		}
		else
		{
			i++;
		}
	}
	return (count);
}

static void	*ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		count;

	if (s == 0)
		return (NULL);
	count = ft_count_words(s, c);
	strs = malloc(sizeof(char *) * (count + 1));
	if (strs == 0)
		return (NULL);
	strs[count] = NULL;
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			strs[i] = ft_substr(s, 0, ft_length_word(s, c));
			if (strs[i++] == 0)
				return (ft_free(strs));
			s += ft_length_word(s, c);
		}
		else
			s++;
	}
	return (strs);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	src_len;

	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	if (start >= src_len)
	{
		substring = ft_calloc(1, sizeof(char));
		if (!substring)
			return (NULL);
		return (substring);
	}
	if (len > src_len - start)
		len = src_len - start;
	substring = ft_calloc(len + 1, sizeof(char));
	if (!substring)
		return (NULL);
	ft_memcpy(substring, s + start, len);
	return (substring);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total;

	total = nmemb * size;
	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(1);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (total / size != nmemb)
		return (NULL);
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp;

	temp = s;
	while (n--)
		*temp++ = 0;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*temp_dest;
	const unsigned char	*temp_src;
	size_t				i;

	if (!dest && !src && n > 0)
		return (NULL);
	if (!n)
		return (dest);
	temp_dest = (unsigned char *)dest;
	temp_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		temp_dest[i] = temp_src[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin_char(const char *str, char c)
{
	char	*result;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	ft_memcpy(result, str, len);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

// extract tokens from strings
// returns a pointer to the next token
// could be useful for handling simple word tokenization
// as tokenizer already handles various types of tokens, not necessary
// char *ft_strtok(char *string, const char *delim)
// {
// 	static char *position;
// 	char		*next;

// 	if (string != NULL)
// 		position = string;
// 	if (position == NULL || *position == '\0')
// 		return (NULL);
// 	while (*position && ft_strchr(delim, *position))
// 		position++;
// 	if (*position == '\0') {
// 		position = NULL;
// 		return (NULL);
// 	}
// 	next = position;
// 	while (*position && !ft_strchr(delim, *position))
// 		position++;
// 	if (*position) {
// 		*position = '\0';
// 		position++;
// 	} else {
// 		position = NULL;
// 	}
// 	return (next);
// }

// int main(void)
// {
// 	char	*string = "Hello there general $USER > >> *";
// 	char	*dup = ft_strdup(string);
// 	char	*token;

// 	token = ft_strtok(dup, " ");
// 	while (token != NULL)
// 	{
// 		printf("%s\n", token);
// 		token = ft_strtok(NULL, " ");
// 	}
// 	free(dup);
// 	return (0);
// }
