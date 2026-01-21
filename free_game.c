#include "cub3d.h"

static void	free_textures(void)
{
	if (g_game->config.no)
		free(g_game->config.no);
	if (g_game->config.so)
		free(g_game->config.so);
	if (g_game->config.we)
		free(g_game->config.we);
	if (g_game->config.ea)
		free(g_game->config.ea);
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
/*
static void	free_images(t_game *game)
{
	if (game->frame.img)
		mlx_delete_image(game->mlx, game->frame.img);
	for (int i = 0; i < 4; i++)
		if (game->tex[i].img)
			mlx_delete_image(game->mlx, game->tex[i].img);
}
*/
void	free_game()
{
	if (!g_game)
		return ;
	free_textures();
	free_map(&g_game->map);
//	free_images(game);
//	if (game->win)
	//	mlx_terminate(game->mlx);
	g_game->win = NULL;
	g_game->mlx = NULL;
}
