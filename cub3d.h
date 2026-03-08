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

typedef struct s_player {
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
	int    pitch;
} t_player;

typedef struct s_config {
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    int     floor_color;
    int     ceil_color;
} t_config;

typedef struct s_map {
    char    **grid;
    int     width;
    int     height;
} t_map;

typedef struct s_game
{
    mlx_t           *mlx;    
    mlx_image_t     *frame;  
    mlx_texture_t   *tex[4]; 
    t_config        config;
    t_map           map;
    t_player        player;
	mlx_image_t     *gun_idle;
    mlx_image_t     *gun_fire;
    int             shoot_counter;
}   t_game;

extern t_game *g_game;

void    parse_cub(char *file);
void    error_exit(char *msg);
void    free_game(void);
void    init_game(void);
void    game_loop(void *param);

#endif