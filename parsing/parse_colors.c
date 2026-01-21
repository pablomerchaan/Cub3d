#include "parsing.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !is_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_rgb_value(char *str)
{
	int	value;

	if (!is_valid_number(str))
		error_exit("Invalid color value");
	value = ft_atoi(str);
	if (value < 0 || value > 255)
		error_exit("Color out of range");
	return (value);
}

static int	build_color(char **rgb)
{
	int	r;
	int	g;
	int	b;

	if (count_args(rgb) != 3)
		error_exit("Invalid color format");
	r = parse_rgb_value(rgb[0]);
	g = parse_rgb_value(rgb[1]);
	b = parse_rgb_value(rgb[2]);
	return ((r << 16) | (g << 8) | b);
}

void	parse_color(int dst, char *str, int sw)
{
	char	*clean;
	char	**rgb;

	if (dst != -1)
		error_exit("Duplicate color");
	clean = ft_strtrim(str, " \t\n");
	if (!clean || clean[0] == '\0')
		error_exit("Invalid color line");
	rgb = ft_split(clean, ',');
	free(clean);
	if (sw == 1)
		g_game->config.floor_color = build_color(rgb);
	else if (sw == 2)
		g_game->config.ceil_color = build_color(rgb);
	free_split(rgb);
}
