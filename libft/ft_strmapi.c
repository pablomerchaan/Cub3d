/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconde-s <mconde-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:21:07 by mconde-s          #+#    #+#             */
/*   Updated: 2024/10/21 16:10:05 by mconde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len_s;
	char	*result;

	i = 0;
	len_s = ft_strlen(s);
	result = malloc(len_s + 1);
	if (!s || !(*f))
		return (NULL);
	if (!result)
		return (NULL);
	while (result && i < len_s)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// int main()
// {
// 	char a[] = "CCCCC";
// 	printf("%s", ft_strmapi(a, ft_nose));
// 	return(0);
// }