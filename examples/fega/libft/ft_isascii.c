/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/06 07:37:02 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* The ft_isascii() function returns zero if the character tests false and
* returns non-zero if the character tests true.
*/

int	ft_isascii(int c)
{
	return ((c >= 0 && c <= 127));
}
