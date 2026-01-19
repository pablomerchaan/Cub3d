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

static void	add_map_line(t_game *game, char *line)
{
	if (is_empty(line))
		error_exit("Empty line inside map");
	append_map_line(&game->map, line);
}

static void	parse_lines(int fd, t_game *game)
{
	char	*line;
	int		map_started;

	map_started = 0;
	while ((line = get_next_line(fd)))
	{
		if (!map_started && is_empty(line))
			free(line);
		else if (!map_started && is_param(line))
			parse_param(line, game);
		else
		{
			if (!is_map_line(line))
				error_exit("Invalid line in map");
			map_started = 1;
			add_map_line(game, line);
		}
	}
}

static void	finalize_parse(t_game *game)
{
	if (!all_params_set(&game->config))
		error_exit("Missing parameters");
	make_map_rectangular(&game->map);
	parse_player(&game->map, &game->player, game);
	validate_map(&game->map);
}

void	parse_cub(char *file, t_game *game)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open .cub file");
	parse_lines(fd, game);
	close(fd);
	finalize_parse(game);
}
