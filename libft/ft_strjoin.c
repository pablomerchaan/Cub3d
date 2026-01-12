/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconde-s <mconde-s@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:02:55 by mconde-s          #+#    #+#             */
/*   Updated: 2025/12/27 16:01:59 by mconde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	s3 = malloc(lens1 + lens2 + 1);
	if (!s3)
		return (NULL);
	ft_strlcpy(s3, s1, lens1 + 1);
	ft_strlcat(s3, s2, lens1 + lens2 + 1);
	return (s3);
}

/* int main()
{
	char s1[] = "";
	char s2[] = "";

	printf("%s\n", ft_strjoin(s1, s2));
	return(0);
}		*/