#include "../../include/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// static void	print_content(void *content)
// {
// 	printf("%s\n", (char *)content);
// }

// int main(void)
// {
// 	char	*string1 = "Hello";
// 	char	*string2 = "Bangkok";
// 	t_list	*node1 = ft_lstnew(string1);
// 	t_list	*node2 = ft_lstnew(string2);

// 	ft_lstadd_back(&node1, node2);
// 	ft_lstiter(node1, print_content);
// 	return (0);
// }
