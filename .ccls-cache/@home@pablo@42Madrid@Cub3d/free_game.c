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

static void	free_images(t_game *game)
{
	if (game->frame.img)
		mlx_destroy_image(game->mlx, game->frame.img);
	for (int i = 0; i < 4; i++)
		if (game->tex[i].img)
			mlx_destroy_image(game->mlx, game->tex[i].img);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_textures(game);
	free_map(&game->map);
	free_images(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	game->mlx = NULL;
}
