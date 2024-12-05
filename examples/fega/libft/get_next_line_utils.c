/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 08:32:48 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/09 10:35:36 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_keep_rest(t_gnlmemo *memo)
{
	char	*rest;
	char	*next_nl;
	int		i;

	next_nl = NULL;
	rest = (char *) malloc(memo->nul - memo->nl);
	if (rest)
	{
		i = -1;
		while (memo->nl[++i + 1])
		{
			rest[i] = memo->nl[i + 1];
			if (rest[i] == '\n' && next_nl == NULL)
				next_nl = &rest[i];
		}
		rest[i] = 0;
		memo->nul = &rest[i];
		free (memo->s);
		memo->s = rest;
		memo->nl = next_nl;
		return ;
	}
	free (memo->s);
	memo->s = NULL;
	memo->malloc_error = 1;
}

static char	*ft_get_line(t_gnlmemo *memo)
{
	char	*result;
	int		i;

	result = (char *) malloc (memo->nl - memo->s + 2);
	if (!result)
	{
		free (memo->s);
		memo->s = NULL;
		memo->malloc_error = 1;
		return (NULL);
	}
	i = -1;
	while (++i < memo->nl - memo->s + 1)
		result[i] = memo->s[i];
	result[i] = 0;
	if (memo->s[i] != 0)
		ft_keep_rest(memo);
	else
	{
		memo->nl = NULL;
		free(memo->s);
		memo->s = NULL;
	}
	return (result);
}

/*
** This fn is get string with new line from memo->s
** If have rest of memo->s use ft_keep_rest to make new memo->s
** If not have new line, this file is read to eof from ft_find_nl
** it return memo->s then set memo->s = NULL
*/
char	*ft_get_next_line(t_gnlmemo *memo)
{
	char	*result;

	if (memo->nl)
		return (ft_get_line (memo));
	result = memo->s;
	memo->s = NULL;
	memo->read_end = 1;
	return (result);
}
