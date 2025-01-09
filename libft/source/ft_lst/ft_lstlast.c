#include "../../include/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	if (lst == NULL)
	{
		return (NULL);
	}
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

// int main(void)
// {
// 	char	*string1 = "Hello";
// 	char	*string2 = "Bangkok";
// 	char	*string3 = "This is the end.";

// 	t_list *node1 = ft_lstnew(string1);
// 	t_list *node2 = ft_lstnew(string2);
// 	t_list *node3 = ft_lstnew(string3);

// 	ft_lstadd_back(&node1, node2);
// 	ft_lstadd_back(&node1, node3);

// 	t_list *last = ft_lstlast(node1);
// 	printf("Content of the last node: %s\n", (char *)last->content);
// 	return (0);
// }
