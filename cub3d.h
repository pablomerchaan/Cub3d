/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cub3d.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: almarti3 <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/03/08 19:31:18 by almarti3		  #+#	#+#			 */
/*   Updated: 2026/03/08 19:31:23 by almarti3		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "getnextline/get_next_line.h"
# include "minilibx/MLX42/include/MLX42/MLX42.h"

# define WIDTH 1280
# define HEIGHT 720
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define MM_SCALE 16
# define MM_WALL 0x888888FF
# define MM_FLOOR 0x00000088
# define MM_PLAYER 0xFF0000FF

typedef struct s_pair
{
	int	x;
	int	y;
}	t_pair;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		pitch;
}	t_player;

typedef struct s_config
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_color;
	int		ceil_color;
}	t_config;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_ray
{
	double	cam_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_dist;
	int		line_h;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_num;
	int		tex_x;
}	t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*frame;
	mlx_texture_t	*tex[4];
	t_config		config;
	t_map			map;
	t_player		player;
	mlx_image_t		*gun_idle;
	mlx_image_t		*gun_fire;
	int				shoot_counter;
}	t_game;

void	parse_cub(t_game *game, char *file);
void	error_exit(t_game *game, char *msg);
void	free_game(t_game *game);
void	init_game(t_game *game);
void	game_loop(void *param);
void	draw_minimap(t_game *game);
void	handle_movement(t_game *game);
void	draw_background(t_game *game);

#endif
