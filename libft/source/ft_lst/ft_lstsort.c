#include "../../include/libft.h"

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	int		temp;
	t_list	*start;

	start = lst;
	while (lst != NULL && lst->next != NULL)
	{
		if ((*cmp)(lst->content, lst->next->content) == 0)
		{
			temp = lst->content;
			lst->content = lst->next->content;
			lst->next->content = temp;
			lst = start;
		}
		else
			lst = lst->next;
	}
	return (start);
}
