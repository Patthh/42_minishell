#include "../../include/minishell.h"

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
