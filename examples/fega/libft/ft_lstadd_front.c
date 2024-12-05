/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/08/13 15:11:41 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Adds the node ’new’ at the end of the list.
*/
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!new)
		return ;
	current = *lst;
	if (current)
		new->next = current;
	*lst = new;
}
