#include "parsing.h"
#include <stdlib.h>
#include <string.h>

/* Encuentra la longitud de la línea más larga del mapa */
int find_longest_line(t_map *map)
{
    int max = 0;
    int i = 0;
    while (i < map->height)
    {
        int len = strlen(map->grid[i]);
        if (len > max)
            max = len;
        i++;
    }
    return max;
}

/* Rellena con espacios una línea hasta length */
char *pad_with_spaces(char *line, int length)
{
    int len = strlen(line);
    char *new_line = malloc(length + 1);
    if (!new_line)
        return NULL;
    memcpy(new_line, line, len);
    for (int i = len; i < length; i++)
        new_line[i] = ' ';
    new_line[length] = '\0';
    free(line);
    return new_line;
}

/* Inicializa la dirección del jugador según char 'N', 'S', 'E', 'W' */
void init_player_direction(t_player *player, char dir)
{
    player->dir_x = 0.0;
    player->dir_y = 0.0;
    player->plane_x = 0.0;
    player->plane_y = 0.0;

    if (dir == 'N')
        player->dir_y = -1.0;
    else if (dir == 'S')
        player->dir_y = 1.0;
    else if (dir == 'E')
        player->dir_x = 1.0;
    else if (dir == 'W')
        player->dir_x = -1.0;
}
