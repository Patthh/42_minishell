/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 08:32:57 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/13 15:47:16 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* 
** init memo->s with memo->bf
** find new line and set it to memo->nl
** set null of memo->s to memo->null
*/
int	ft_init_str(t_gnlmemo *memo)
{
	size_t	i;

	i = -1;
	memo->s = (char *) malloc (sizeof (char) * memo->read_ret + 1);
	if (!memo->s)
		return (1);
	while (memo->bf[++i] != 0)
	{
		memo->s[i] = memo->bf[i];
		if (memo->s[i] == '\n' && memo->nl == NULL)
			memo->nl = &memo->s[i];
	}
	memo->s[i] = 0;
	memo->nul = &memo->s[i];
	return (0);
}

/* 
** join memo->s with memo->bf
** find new line and set it to memo->nl
** set null of memo->s to memo->null
** set memo->s with new string joined and free old memo->s
*/
int	ft_join_str(t_gnlmemo *memo)
{
	char	*tab;
	size_t	s_len;
	size_t	new_len;
	int		i;

	s_len = memo->nul - memo->s;
	new_len = s_len + memo->read_ret;
	tab = (char *) malloc (new_len + 1);
	if (!tab)
		return (1);
	i = -1;
	while (++i < (int) s_len)
		tab[i] = memo->s[i];
	i = -1;
	while (++i < (int) memo->read_ret)
	{
		tab[i + s_len] = memo->bf[i];
		if (tab[i + s_len] == '\n' && memo->nl == NULL)
			memo->nl = &tab[i + s_len];
	}
	tab[i + s_len] = 0;
	free (memo->s);
	memo->nul = &tab[i + s_len];
	memo->s = tab;
	return (0);
}

/*
** read file to buffer (memo->bf)
** if memo->s == NULL, init string to memo->s
** else join memo->s with memo->bf
*/
void	ft_find_nl(t_gnlmemo *memo, int fd)
{
	while (!memo->nl && !memo->malloc_error)
	{
		memo->read_ret = read(fd, memo->bf, BUFFER_SIZE);
		if (memo->read_ret < 1)
			break ;
		(memo->bf)[memo->read_ret] = 0;
		if (!memo->s)
			memo->malloc_error = ft_init_str (memo);
		else
			memo->malloc_error = ft_join_str (memo);
	}
}

/*This code pass Tripouille test case in 120000 micro sec*/
char	*get_next_line(int fd)
{
	static t_gnlmemo	memo[FD_MAX];

	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE < 1 || memo[fd].malloc_error)
		return (NULL);
	memo[fd].bf = (char *) malloc (BUFFER_SIZE + 1);
	if (!memo[fd].bf)
	{
		memo[fd].malloc_error = 1;
		return (NULL);
	}
	if (!memo[fd].nl)
		ft_find_nl(&memo[fd], fd);
	free (memo[fd].bf);
	if (memo[fd].read_ret == -1 || memo[fd].malloc_error)
	{
		if (memo[fd].s)
			free (memo[fd].s);
		memo[fd].s = NULL;
	}
	if (!memo[fd].s)
		return (NULL);
	return (ft_get_next_line(&memo[fd]));
}
