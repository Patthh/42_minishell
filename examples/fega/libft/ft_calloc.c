/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/27 11:30:09 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The ft_calloc() function contiguously allocates enough 
	space for count objects
	that are size bytes of memory each and returns a pointer to the allocated
	memory.  The allocated memory is filled with bytes of value zero.
*/

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;

	tab = malloc (count * size);
	if (!tab)
		return (NULL);
	ft_memset (tab, 0, count * size);
	return (tab);
}
