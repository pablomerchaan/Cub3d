/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init_game.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: almarti3 <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/03/08 19:31:42 by almarti3		  #+#	#+#			 */
/*   Updated: 2026/03/08 19:31:44 by almarti3		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

static void	load_textures(t_game *game)
{
	game->tex[0] = mlx_load_png(game->config.no);
	if (!game->tex[0])
		error_exit(game, "Failed to load NO texture");
	game->tex[1] = mlx_load_png(game->config.so);
	if (!game->tex[1])
		error_exit(game, "Failed to load SO texture");
	game->tex[2] = mlx_load_png(game->config.we);
	if (!game->tex[2])
		error_exit(game, "Failed to load WE texture");
	game->tex[3] = mlx_load_png(game->config.ea);
	if (!game->tex[3])
		error_exit(game, "Failed to load EA texture");
}

static void	init_weapon(t_game *game)
{
	mlx_texture_t	*t_idle;
	mlx_texture_t	*t_fire;
	int				x;
	int				y;

	t_idle = mlx_load_png("textures/gun.png");
	t_fire = mlx_load_png("textures/gun_fire.png");
	if (!t_idle || !t_fire)
		error_exit(game, "Failed to load weapon textures");
	game->gun_idle = mlx_texture_to_image(game->mlx, t_idle);
	game->gun_fire = mlx_texture_to_image(game->mlx, t_fire);
	mlx_delete_texture(t_idle);
	mlx_delete_texture(t_fire);
	x = (WIDTH / 2) - (game->gun_idle->width / 2) + 200;
	y = HEIGHT - game->gun_idle->height;
	if (mlx_image_to_window(game->mlx, game->gun_idle, x, y) < 0
		|| mlx_image_to_window(game->mlx, game->gun_fire, x, y) < 0)
		error_exit(game, "Weapon connection failed");
	game->gun_idle->instances[0].enabled = true;
	game->gun_fire->instances[0].enabled = false;
	game->shoot_counter = 0;
}

void	init_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
		game->tex[i++] = NULL;
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D - Bonus", true);
	if (!game->mlx)
		error_exit(game, "MLX42 init failed");
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	game->frame = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->frame)
		error_exit(game, "Frame creation failed");
	if (mlx_image_to_window(game->mlx, game->frame, 0, 0) < 0)
		error_exit(game, "Window connection failed");
	load_textures(game);
	init_weapon(game);
}
