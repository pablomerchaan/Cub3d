/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconde-s <mconde-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:00:36 by mconde-s          #+#    #+#             */
/*   Updated: 2024/10/18 18:31:06 by mconde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_num(int n)
{
	size_t	count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	if (n == 0)
		count = 1;
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*nbr;

	len = count_num(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nbr = ft_calloc(len + 1, sizeof(char));
	if (!nbr)
		return (NULL);
	if (n < 0)
	{
		nbr[0] = '-';
		n = -n;
	}
	nbr[len--] = '\0';
	while ((n > 9))
	{
		nbr[len--] = (n % 10) + '0';
		n = n / 10;
	}
	nbr[len] = n + '0';
	return (nbr);
}

/* int main()
{
	int	n;

	n = 1223;
	printf("%s", ft_itoa(n));
	return(0);
}
 */