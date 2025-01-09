#include "../../include/libft.h"

void	ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	t_list	*current;

	current = begin_list;
	while (current != NULL)
	{
		(*f)(current->content);
		current = current->next;
	}
}
