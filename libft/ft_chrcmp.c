/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconde-s <mconde-s@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:51:54 by mconde-s          #+#    #+#             */
/*   Updated: 2025/11/05 17:37:33 by mconde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Esta función hace tantas cosas que ya no se que hace
 * @warning Hay que mejorar esta función, muy cutre XD
 */
int	ft_chrcmp(char *str, char *c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (str[i] && str[i + 1] == c[0] && c[0] == '|')
		return (1);
	while (str[i])
	{
		if (str[i] == c[0] && str[i + 1] && c[1] && str[i + 1] == c[1]
			&& len == 2)
			return (2);
		if (str[i] == c[0] && (len == 1 || len == 2))
			return (0);
		i++;
	}
	return (1);
}
