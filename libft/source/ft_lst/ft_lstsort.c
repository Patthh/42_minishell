/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:50:17 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:50:18 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
