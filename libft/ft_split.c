/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconde-s <mconde-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:25:39 by mconde-s          #+#    #+#             */
/*   Updated: 2024/10/22 21:06:33 by mconde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(char **result)
{
	size_t	position;

	position = 0;
	while (result[position])
		free(result[position++]);
	free(result);
	return (NULL);
}

static int	count_sub(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	**ft_filler(char const *s, char c, size_t i, size_t j)
{
	size_t	start;
	char	**aux;

	aux = ft_calloc((count_sub(s, c) + 1), sizeof(char *));
	if (!aux)
		return (NULL);
	start = 0;
	while (1)
	{
		if (s[i] == c || s[i] == 0)
		{
			if (i > start)
			{
				aux[j] = ft_substr(s, start, i - start);
				if (!aux[j++])
					return (ft_free(aux));
			}
			start = i + 1;
			if (s[i] == 0)
				break ;
		}
		i++;
	}
	aux[j] = NULL;
	return (aux);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = ft_filler(s, c, 0, 0);
	if (!result)
		return (NULL);
	return (result);
}

// int main()
// {
//    char    a[] = "lorem ipsum dolor sit amet,";
//    char **resultado = ft_split(a, ' ');
//    printf("%s\n",resultado[0]);
//    printf("%s\n",resultado[1]);
//    printf("%s\n",resultado[2]);
//    printf("%s\n",resultado[3]);
//    free(resultado[1]);
//    free(resultado[2]);
//    free(resultado[3]);
//    free(resultado[0]);
//    free(resultado);
//    return (0);
// }
