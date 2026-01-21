#include "parsing/parsing.h"
#include <stdio.h>

t_game *g_game = NULL;

static void print_config(void)
{
    printf("=== TEXTURES ===\n");
    printf("NO: %s\n", g_game->config.no);
    printf("SO: %s\n", g_game->config.so);
    printf("WE: %s\n", g_game->config.we);
    printf("EA: %s\n", g_game->config.ea);

    printf("\n=== COLORS ===\n");
    printf("Floor:   %d (0x%06X)\n",
        g_game->config.floor_color, g_game->config.floor_color);
    printf("Ceiling: %d (0x%06X)\n",
        g_game->config.ceil_color, g_game->config.ceil_color);
}

static void print_player(void)
{
    printf("\n=== PLAYER ===\n");
    printf("Position: (%.2f, %.2f)\n",
        g_game->player.x, g_game->player.y);
    printf("Direction: (%.2f, %.2f)\n",
        g_game->player.dir_x, g_game->player.dir_y);
    printf("Plane: (%.2f, %.2f)\n",
        g_game->player.plane_x, g_game->player.plane_y);
}

static void print_map(void)
{
    int i;

    printf("\n=== MAP ===\n");
    printf("Size: %d x %d\n",
        g_game->map.width, g_game->map.height);

    i = 0;
    while (i < g_game->map.height)
    {
        printf("%s\n", g_game->map.grid[i]);
        i++;
    }
}

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

    init_game();
		parse_cub(argv[1]);
/*
    if (!parse_cub(argv[1]))
    {
        printf("❌ Parse error\n");
        free_game();
        return (1);
    }
*/
    printf("✅ Parse OK\n\n");

    print_config();
    print_player();
    print_map();

    free_game();
    return (0);
}
