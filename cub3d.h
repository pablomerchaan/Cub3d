#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
#include "libft/libft.h"
#include "mlx/include/MLX42/MLX42.h"
#include "getnextline/get_next_line.h"

typedef struct s_player {
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_config {
	char *no;
	char *so;
	char *we;
	char *ea;
	int floor_color;
	int ceil_color;
} t_config;

typedef struct s_map {
	char **grid;
	int width;
	int height;
} t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_config	config;
	t_map		map;
	t_player	player;
	t_img		frame;
	t_img		tex[4];
}	t_game;

void	parse_cub(char *file, t_game *game);
void	error_exit(char *msg);
void	free_game(t_game *game);
void	init_game(t_game *game);

#endif
