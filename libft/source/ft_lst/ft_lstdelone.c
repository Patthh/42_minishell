/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:50:04 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:50:05 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
	{
		return ;
	}
	del(lst->content);
	free(lst);
}

// int main(void)
// {
// 	char	*string = "Hello, Bangkok!";
// 	t_list	*node = ft_lstnew(string);

// 	if (node != NULL)
// 	{
// 		ft_lstdelone(node, NULL);
// 		printf("Node deleted\n");
// 	}
// 	else
// 		printf("Failed to create node\n");
// 	return (0);
// }
