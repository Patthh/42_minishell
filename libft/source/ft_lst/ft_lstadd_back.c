#include "../../include/libft.h"

// adds a node to the end of a list
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	current = *lst;
	if (current == NULL)
	{
		*lst = new;
		return ;
	}
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
}

// int main(void)
// {
// 	char	*string1 = "Hello";
// 	char	*string2 = "Bangkok!";

// 	t_list	*node1 = ft_lstnew(string1);
// 	t_list	*node2 = ft_lstnew(string2);

// 	ft_lstadd_back(&node1, node2);

// 	printf("%s\n", (char *)node1->content);
// 	printf("%s\n", (char *)node1->next->content);
// 	return (0);
// }
