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

static void	init_images(void)
{
	int	i;

	g_game->frame.img = NULL;
	g_game->frame.addr = NULL;
	g_game->frame.width = 0;
	g_game->frame.height = 0;
	i = 0;
	while (i < 4)
	{
		g_game->tex[i].img = NULL;
		g_game->tex[i].addr = NULL;
		g_game->tex[i].width = 0;
		g_game->tex[i].height = 0;
		i++;
	}
}

void	init_game()
{
	g_game->mlx = NULL;
	g_game->win = NULL;
	init_config(&g_game->config);
	init_map(&g_game->map);
	init_player(&g_game->player);
	init_images();
}
