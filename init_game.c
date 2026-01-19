#include "cub3d.h"

static void	init_config(t_config *cfg)
{
	cfg->no = NULL;
	cfg->so = NULL;
	cfg->we = NULL;
	cfg->ea = NULL;
	cfg->floor_color = -1;
	cfg->ceil_color = -1;
}

static void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
}

static void	init_player(t_player *p)
{
	p->x = 0;
	p->y = 0;
	p->dir_x = 0;
	p->dir_y = 0;
	p->plane_x = 0;
	p->plane_y = 0;
}

static void	init_images(t_game *game)
{
	int	i;

	game->frame.img = NULL;
	game->frame.addr = NULL;
	game->frame.width = 0;
	game->frame.height = 0;
	i = 0;
	while (i < 4)
	{
		game->tex[i].img = NULL;
		game->tex[i].addr = NULL;
		game->tex[i].width = 0;
		game->tex[i].height = 0;
		i++;
	}
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	init_config(&game->config);
	init_map(&game->map);
	init_player(&game->player);
	init_images(game);
}
