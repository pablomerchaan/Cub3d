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

static void	handle_line(char *clean, int *started)
{
	if (!*started && is_empty(clean))
		free(clean);
	else if (!*started && is_param(clean))
	{
		parse_param(clean);
		free(clean);
	}
	else
	{
		if (!is_map_line(clean))
			error_exit("Invalid line in map");
		*started = 1;
		append_map_line(&g_game->map, clean);
	}
}

static void	parse_lines(int fd)
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
		handle_line(clean, &started);
		line = get_next_line(fd);
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
