/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   free_game.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: almarti3 <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/03/08 19:31:32 by almarti3		  #+#	#+#			 */
/*   Updated: 2026/03/08 19:31:34 by almarti3		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_game *game)
{
	if (game->config.no)
		free(game->config.no);
	if (game->config.so)
		free(game->config.so);
	if (game->config.we)
		free(game->config.we);
	if (game->config.ea)
		free(game->config.ea);
}

static void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i])
			free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
}

void	free_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->tex[i])
			mlx_delete_texture(game->tex[i]);
		i++;
	}
	free_textures(game);
	free_map(&game->map);
	game->mlx = NULL;
}
