/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconde-s <mconde-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:29:23 by mconde-s          #+#    #+#             */
/*   Updated: 2024/10/18 18:51:07 by mconde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*src2;
	unsigned char	*dest2;
	size_t			i;

	if (!dest && !src)
		return (dest);
	src2 = (unsigned char *)src;
	dest2 = (unsigned char *)dest;
	if (dest2 < src2)
	{
		i = 0;
		while (i++ < n)
			dest2[i - 1] = src2[i - 1];
		return (dest);
	}
	else if (dest2 > src2)
	{
		i = n;
		while (i > 0)
		{
			dest2[i - 1] = src2[i - 1];
			i--;
		}
	}
	return (dest);
}
// int main()
// {
// 	char src[] = "TodoMal";
// 	char dest[] = "NoPasaNada";
// 	printf("%s\n",(char *)ft_memmove(dest, src, 12));
// 	return(0);
// }