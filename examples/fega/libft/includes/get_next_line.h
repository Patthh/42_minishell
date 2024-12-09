/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:06:52 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/13 15:46:19 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

typedef struct s_gnlmemo
{
	char	*s;
	char	*bf;
	char	*nl;
	char	*nul;
	int		read_ret;
	int		malloc_error;
	int		read_end;
}	t_gnlmemo;

char	*get_next_line(int fd);

// utils
int		ft_init_str(t_gnlmemo *memo);
int		ft_join_str(t_gnlmemo *memo);
void	ft_find_nl(t_gnlmemo *memo, int fd);
void	ft_keep_rest(t_gnlmemo *memo);
char	*ft_get_next_line(t_gnlmemo *memo);

#endif
