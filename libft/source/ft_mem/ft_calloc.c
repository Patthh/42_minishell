/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:50:22 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:50:23 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

//allocates and zeroes memory
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total;

	total = nmemb * size;
	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(1);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (total / size != nmemb)
		return (NULL);
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}

// int main(void) {
// 	size_t nmemb = 5;
// 	size_t size = sizeof(int);
// 	int *array = (int *)calloc(nmemb, size);
// 	int *ft_array = (int *)ft_calloc(nmemb, size);
// 	printf("Results from calloc:\n");
// 	size_t i = 0;
// 	while (i < nmemb) {
// 		printf("array[%zu] = %d\n", i, array[i]);
// 		i++;
// 	}
// 	printf("\nResults from ft_calloc:\n");
// 	i = 0;
// 	while (i < nmemb) {
// 		printf("ft_array[%zu] = %d\n", i, ft_array[i]);
// 		i++;
// 	}
// 	free(ft_array);
// 	free(array);
// 	return 0;
// }
