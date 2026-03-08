#include "cub3d.h"

t_game *g_game = NULL;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s map.cub\n", argv[0]);
        return (1);
    }

    g_game = malloc(sizeof(t_game));
    if (!g_game)
        return (1);

    // Inicialización pre-parser
    g_game->config.floor_color = -1;
    g_game->config.ceil_color = -1;
    g_game->config.no = NULL;
    g_game->config.so = NULL;
    g_game->config.we = NULL;
    g_game->config.ea = NULL;
    g_game->map.grid = NULL;
    g_game->map.width = 0;
    g_game->map.height = 0;
    g_game->mlx = NULL; 
    g_game->frame = NULL;
    g_game->player.pitch = 0;

    parse_cub(argv[1]);
    init_game();

    mlx_loop_hook(g_game->mlx, game_loop, NULL);
    mlx_loop(g_game->mlx);

    mlx_terminate(g_game->mlx); 
    free_game();                
    free(g_game);
    
    return (0);
}