/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarti3 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:25:05 by almarti3          #+#    #+#             */
/*   Updated: 2026/03/08 18:25:07 by almarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

int	find_longest_line(t_map *map)
{
	int	max;
	int	i;
	int	len;

	max = 0;
	i = 0;
	while (i < map->height)
	{
		len = ft_strlen(map->grid[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

char	*pad_with_spaces(char *line, int length)
{
	int		len;
	int		i;
	char	*new_line;

	len = ft_strlen(line);
	new_line = malloc(length + 1);
	if (!new_line)
		return (NULL);
	ft_memcpy(new_line, line, len);
	i = len;
	while (i < length)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[length] = '\0';
	free(line);
	return (new_line);
}

void	init_player_direction(t_player *player, char dir)
{
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	if (dir == 'N')
	{
		player->dir_y = -1.0;
		player->plane_x = 0.66;
	}
	else if (dir == 'S')
	{
		player->dir_y = 1.0;
		player->plane_x = -0.66;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1.0;
		player->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1.0;
		player->plane_y = -0.66;
	}
}

void	append_map_line(t_game *game, t_map *map, char *line)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (map->height + 2));
	if (!new_grid)
		error_exit(game, "Malloc failed");
	i = 0;
	while (i < map->height)
	{
		new_grid[i] = map->grid[i];
		i++;
	}
	new_grid[i] = line;
	new_grid[i + 1] = NULL;
	if (map->grid)
		free(map->grid);
	map->grid = new_grid;
	map->height++;
}
