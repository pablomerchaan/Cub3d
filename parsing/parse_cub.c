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

    free(map->grid);
    map->grid = new_grid;
    map->height++;
}

static void	add_map_line(char *line)
{
	char *copy;
	if (is_empty(line))
		error_exit("Empty line inside map");
	copy = ft_strdup(line);
	append_map_line(&g_game->map, copy);
}

static void	parse_lines(int fd)
{
	char	*line;
	int		map_started;

	map_started = 0;
	while ((line = get_next_line(fd)))
	{
		if (!map_started && is_empty(line))
			free(line);
		else if (!map_started && is_param(line))
			parse_param(line);
		else
		{
			if (!is_map_line(line))
				error_exit("Invalid line in map");
			map_started = 1;
			add_map_line(line);
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
