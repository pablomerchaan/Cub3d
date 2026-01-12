/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconde-s <mconde-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:56:22 by mconde-s          #+#    #+#             */
/*   Updated: 2024/10/18 22:20:19 by mconde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

// int main()
// {
// 	int fd;
// 	char s[] = "hellothere";
// 	fd = open("txt4.txt", O_RDWR);
// 	printf("%d", fd);
// 	ft_putendl_fd(s, fd);
// }