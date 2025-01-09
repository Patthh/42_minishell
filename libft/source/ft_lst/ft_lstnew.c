#include "../../include/libft.h"

// creates a new list node
t_list	*ft_lstnew(void *content)
{
	t_list	*pointer;

	pointer = (t_list *)malloc(sizeof(t_list));
	if (pointer == NULL)
	{
		return (NULL);
	}
	pointer->content = content;
	pointer->next = NULL;
	return (pointer);
}

// int main(void)
// {
// 	char	*string = "Hello, Bangkok!";
// 	t_list	*node = ft_lstnew(string);

// 	printf("%s\n", (char *)node->content);
// 	free(node);
// 	return (0);
// }
