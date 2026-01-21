#include "parsing.h"

int	is_param(char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (1);
	if (!ft_strncmp(line, "SO ", 3))
		return (1);
	if (!ft_strncmp(line, "WE ", 3))
		return (1);
	if (!ft_strncmp(line, "EA ", 3))
		return (1);
	if (!ft_strncmp(line, "F ", 2))
		return (1);
	if (!ft_strncmp(line, "C ", 2))
		return (1);
	return (0);
}

void	parse_param(char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		parse_texture(&g_game->config.no, line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		parse_texture(&g_game->config.so, line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		parse_texture(&g_game->config.we, line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		parse_texture(&g_game->config.ea, line + 3);
	else if (!ft_strncmp(line, "F ", 2))
		parse_color(g_game->config.floor_color, line + 2, 1);
	else if (!ft_strncmp(line, "C ", 2))
		parse_color(g_game->config.ceil_color, line + 2, 2);
	else
		error_exit("Unknown parameter");
}

int	all_params_set(t_config *cfg)
{
	printf ("%s\n", cfg->no);
	printf ("%s\n", cfg->so);
	printf ("%s\n", cfg->ea);
	printf ("%s\n", cfg->we);
	printf ("%i\n", cfg->ceil_color);
	printf ("%i\n", cfg->floor_color);
	if (!cfg->no || !cfg->so || !cfg->we || !cfg->ea)
		return (0);
	if (cfg->floor_color == -1 || cfg->ceil_color == -1)
		return (0);
	return (1);
}
