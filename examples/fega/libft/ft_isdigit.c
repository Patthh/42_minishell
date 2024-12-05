/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/06 07:37:23 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* The ft_isdigit() function returns zero if the character tests false and
* returns non-zero if the character tests true.
*/

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}
