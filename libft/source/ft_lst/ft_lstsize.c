/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:50:15 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:50:16 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = lst;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

// int main(void)
// {
// 	char	*string1 = "Hello";
// 	char	*string2 = "Bangkok";
// 	char	*string3 = "something";

// 	t_list *node1 = ft_lstnew(string1);
// 	t_list *node2 = ft_lstnew(string2);
// 	t_list *node3 = ft_lstnew(string3);

// 	ft_lstadd_back(&node1, node2);
// 	ft_lstadd_back(&node1, node3);

// 	printf("List size: %d\n", ft_lstsize(node1));
// 	return (0);
// }
