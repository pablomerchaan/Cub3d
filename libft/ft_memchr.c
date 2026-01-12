/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconde-s <mconde-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:47:39 by mconde-s          #+#    #+#             */
/*   Updated: 2024/10/18 18:34:33 by mconde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s1;
	size_t			i;

	s1 = (unsigned char *)s;
	i = 0;
	c = (unsigned char)c;
	while (i < n)
	{
		if (s1[i] == c)
			return (s1 + i);
		i++;
	}
	return (NULL);
}
// int	main(void)
// {
// 	char a[] = "HelloThere";
// 	char *b;
// 	b = ft_memchr(a, 'e', 4);
// 	printf("%c", (*b));
// 	return (0);
// }