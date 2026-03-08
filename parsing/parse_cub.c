#include "parsing.h"

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void append_map_line(t_map *map, char *line)
{
    char    **new_grid;
    int     i;

    new_grid = malloc(sizeof(char *) * (map->height + 2));
    if (!new_grid)
        error_exit("Malloc failed");

    i = 0;
    while (i < map->height)
    {
        new_grid[i] = map->grid[i];
        i++;
    }

    new_grid[i] = line;
    new_grid[i + 1] = NULL;

    if (map->grid)
        free(map->grid);
    map->grid = new_grid;
    map->height++;
}

static void	parse_lines(int fd)
{
	char	*line;
	int		map_started;
    char    *clean_line;

	map_started = 0;
	while ((line = get_next_line(fd)))
	{
        // En caso de que GNL traiga saltos de línea al final, limpiamos
        clean_line = ft_strtrim(line, "\n");
        free(line); // Liberamos la original de GNL de inmediato
        
		if (!map_started && is_empty(clean_line))
			free(clean_line);
		else if (!map_started && is_param(clean_line))
        {
			parse_param(clean_line);
            free(clean_line);
        }
		else
		{
			if (!is_map_line(clean_line))
				error_exit("Invalid line in map");
			map_started = 1;
            // append_map_line ahora "posee" este puntero. No le hacemos free aquí.
			append_map_line(&g_game->map, clean_line); 
		}
	}
}

static void	finalize_parse(void)
{
	if (!all_params_set(&g_game->config))
		error_exit("Missing parameters");
	make_map_rectangular(&g_game->map);
	parse_player(&g_game->map, &g_game->player);
	validate_map(&g_game->map);
}

void	parse_cub(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open .cub file");
	parse_lines(fd);
	close(fd);
	finalize_parse();
}