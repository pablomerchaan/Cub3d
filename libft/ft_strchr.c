/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconde-s <mconde-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:54:30 by mconde-s          #+#    #+#             */
/*   Updated: 2024/10/17 16:43:13 by mconde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

/* int	main(void)
{
	char	a[] = "123443434helloThere";

	printf("%s", ft_strchr(a, 'h'));
	return (0);
} */
