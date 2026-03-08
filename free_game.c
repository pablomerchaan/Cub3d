#include "cub3d.h"

static void free_textures(void)
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

static void free_map(t_map *map)
{
    int i;

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

void    free_game(void)
{
    int i;

    if (!g_game)
        return ;
    
    // 1. Destruir las texturas de VRAM/RAM
    i = 0;
    while (i < 4)
    {
        if (g_game->tex[i])
            mlx_delete_texture(g_game->tex[i]);
        i++;
    }

    // 2. Liberar memoria estándar
    free_textures(); // Libera los strings de las rutas
    free_map(&g_game->map);
    g_game->mlx = NULL;
}