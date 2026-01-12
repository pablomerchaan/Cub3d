/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconde-s <mconde-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:47:42 by mconde-s          #+#    #+#             */
/*   Updated: 2024/10/18 19:12:05 by mconde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
	size_t	lens;

	if (!s)
		return ;
	i = 0;
	lens = ft_strlen(s);
	while (s[i])
		i++;
	write(fd, s, lens);
}
// int	main(void)
// {
// 	int	fd;
// 	char s[] = "buenosdias";

// 	fd = open("txt2.txt", O_RDWR);
// 	printf("%d", fd);
// 	ft_putstr_fd(s, fd);
// }