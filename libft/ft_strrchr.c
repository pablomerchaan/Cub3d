/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconde-s <mconde-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:28:19 by mconde-s          #+#    #+#             */
/*   Updated: 2024/10/22 21:08:02 by mconde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*final_c;

	final_c = NULL;
	while (*s)
	{
		if (*s == (char)c)
			final_c = s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return ((char *)final_c);
}

// int	main(void)
// {
// 	char *a = ":1234:)HelloThere";
// 	printf("%s", ft_strrchr(a, 'H'));
// 	return (0);
// }
