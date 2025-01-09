#include "../../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*temp;

	new_lst = NULL;
	if (lst == NULL || f == NULL || del == NULL)
	{
		return (NULL);
	}
	while (lst)
	{
		temp = ft_lstnew(f(lst->content));
		if (temp == NULL)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, temp);
		lst = lst-> next;
	}
	return (new_lst);
}

// static void	del(void *content)
// {
// 	(void)content;
// }

// static void	*capitalizer(void *content)
// {
// 	char	*str;
// 	char	*new_str;
// 	int		i;

// 	str = (char *)content;
// 	new_str = ft_strdup(str);
// 	if (!new_str)
// 		return (NULL);
// 	i = 0;
// 	while (new_str[i])
// 	{
// 		if (new_str[i] >= 'a' && new_str[i] <= 'z')
// 			new_str[i] -= 32;
// 		i++;
// 	}
// 	return ((void *)new_str);
// }

// int main(void)
// {
// 	char	*string1 = "hello";
// 	char	*string2 = "bangkok";
// 	t_list	*node1 = ft_lstnew(string1);
// 	t_list	*node2 = ft_lstnew(string2);
// 	t_list	*new_list;

// 	ft_lstadd_back(&node1, node2);
// 	new_list = ft_lstmap(node1, capitalizer, del);

// 	while (new_list)
// 	{
// 		printf("%s\n", (char *)new_list->content);
// 		new_list = new_list->next;
// 	}
// 	ft_lstclear(&node1, del);
// 	ft_lstclear(&new_list, del);
// 	return (0);
// }
