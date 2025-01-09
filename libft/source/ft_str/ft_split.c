#include "../../include/libft.h"

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

// int main(void)
// {
// 	char **result = ft_split("Hello,Bangkok,!", ',');
// 	int i = 0;

// 	while (result[i])
// 	{
// 		printf("%s\n", result[i]);
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);

// 	return 0;
// }
