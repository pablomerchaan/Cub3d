/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parse_cub.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: almarti3 <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/03/08 18:24:08 by almarti3		  #+#	#+#			 */
/*   Updated: 2026/03/08 18:24:09 by almarti3		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

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

static void	handle_line(t_game *game, char *clean, int *started)
{
	if (!*started && is_empty(clean))
		free(clean);
	else if (!*started && is_param(clean))
	{
		parse_param(game, clean);
		free(clean);
	}
	else
	{
		if (!is_map_line(clean))
			error_exit(game, "Invalid line in map");
		*started = 1;
		append_map_line(game, &game->map, clean);
	}
}

static void	parse_lines(t_game *game, int fd)
{
	char	*line;
	int		started;
	char	*clean;

	started = 0;
	line = get_next_line(fd);
	while (line)
	{
		clean = ft_strtrim(line, "\n");
		free(line);
		handle_line(game, clean, &started);
		line = get_next_line(fd);
	}
}

static void	finalize_parse(t_game *game)
{
	if (!all_params_set(&game->config))
		error_exit(game, "Missing parameters");
	make_map_rectangular(&game->map);
	parse_player(game, &game->map, &game->player);
	validate_map(game, &game->map);
}

void	parse_cub(t_game *game, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit(game, "Cannot open .cub file");
	parse_lines(game, fd);
	close(fd);
	finalize_parse(game);
}
