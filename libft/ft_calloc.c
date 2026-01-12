/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconde-s <mconde-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:54:16 by mconde-s          #+#    #+#             */
/*   Updated: 2024/10/22 21:19:33 by mconde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*a;
	size_t	i;

	if ((nmemb * size < nmemb || nmemb * size < size) && size && nmemb)
		return (0);
	a = malloc(nmemb * size);
	i = 0;
	while (i < nmemb * size && a)
	{
		a[i] = 0;
		i++;
	}
	return (a);
}
// int main()
// {
// 	char *a;
// 	a = ft_calloc(0, sizeof(char));
// 	return(0);
// }