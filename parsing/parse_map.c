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

static void	set_player(t_game *game, int x, int y, char dir)
{
	if (game->player.dir_x != 0 || game->player.dir_y != 0)
		error_exit(game, "Multiple players");
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	init_player_direction(&game->player, dir);
}

void	parse_player(t_game *game, t_map *map, t_player *player)
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
				set_player(game, j, i, map->grid[i][j]);
				map->grid[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (player->dir_x == 0 && player->dir_y == 0)
		error_exit(game, "No player found");
}
