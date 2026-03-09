/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarti3 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:23:34 by almarti3          #+#    #+#             */
/*   Updated: 2026/03/08 18:23:37 by almarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_walkable(char c)
{
	return (c == '0');
}

static void	check_cell(t_game *game, t_map *map, int i, int j)
{
	if (i == 0 || j == 0
		|| i == map->height - 1
		|| j == map->width - 1)
		error_exit(game, "Map not closed");
	if (map->grid[i - 1][j] == ' '
		|| map->grid[i + 1][j] == ' '
		|| map->grid[i][j - 1] == ' '
		|| map->grid[i][j + 1] == ' ')
		error_exit(game, "Map not closed");
}

void	validate_map(t_game *game, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (is_walkable(map->grid[i][j]))
				check_cell(game, map, i, j);
			j++;
		}
		i++;
	}
}
