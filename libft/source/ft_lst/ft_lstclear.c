/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:50:03 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:50:04 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone (*lst, del);
		*lst = temp;
	}
}

// int main(void)
// {
// 	char	*string1 = "Hello";
// 	char	*string2 = "Bangkok";
// 	t_list	*node1 = ft_lstnew(string1);
// 	t_list	*node2 = ft_lstnew(string2);

// 	ft_lstadd_back(&node1, node2);
// 	ft_lstclear(&node1, NULL);

// 	if (node1 == NULL)
// 		printf("List cleared\n");
// 	else
// 		printf("List not cleared\n");

// 	return (0);
// }
