/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconde-s <mconde-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:10:42 by mconde-s          #+#    #+#             */
/*   Updated: 2024/10/21 15:54:59 by mconde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	if (f == 0)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// int	main()
// {
// 	char *a = "HelloThero";
// 	ft_striteri(a, &ft_write);
// 	return 0;
// }