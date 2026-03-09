/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarti3 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:23:59 by almarti3          #+#    #+#             */
/*   Updated: 2026/03/08 18:24:01 by almarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	parse_rgb_value(t_game *game, char *str)
{
	int	value;

	if (!is_valid_number(str))
		error_exit(game, "Invalid color value");
	value = ft_atoi(str);
	if (value < 0 || value > 255)
		error_exit(game, "Color out of range");
	return (value);
}

static int	build_color(t_game *game, char **rgb)
{
	int	r;
	int	g;
	int	b;

	if (count_args(rgb) != 3)
		error_exit(game, "Invalid color format");
	r = parse_rgb_value(game, rgb[0]);
	g = parse_rgb_value(game, rgb[1]);
	b = parse_rgb_value(game, rgb[2]);
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

void	parse_color(t_game *game, int dst, char *str, int sw)
{
	char	*clean;
	char	**rgb;

	if (dst != -1)
		error_exit(game, "Duplicate color");
	clean = ft_strtrim(str, " \t\n");
	if (!clean || clean[0] == '\0')
		error_exit(game, "Invalid color line");
	rgb = ft_split(clean, ',');
	free(clean);
	if (sw == 1)
		game->config.floor_color = build_color(game, rgb);
	else if (sw == 2)
		game->config.ceil_color = build_color(game, rgb);
	free_split(rgb);
}
