/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarti3 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:25:24 by almarti3          #+#    #+#             */
/*   Updated: 2026/03/08 18:25:26 by almarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	make_map_rectangular(t_map *map)
{
	int	i;
	int	max;

	max = find_longest_line(map);
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = pad_with_spaces(map->grid[i], max);
		i++;
	}
	map->width = max;
}

static void	set_player(int x, int y, char dir)
{
	if (g_game->player.dir_x != 0 || g_game->player.dir_y != 0)
		error_exit("Multiple players");
	g_game->player.x = x + 0.5;
	g_game->player.y = y + 0.5;
	init_player_direction(&g_game->player, dir);
}

void	parse_player(t_map *map, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (ft_strchr("NSEW", map->grid[i][j]))
			{
				set_player(j, i, map->grid[i][j]);
				map->grid[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (player->dir_x == 0 && player->dir_y == 0)
		error_exit("No player found");
}
