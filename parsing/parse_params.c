/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarti3 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:25:35 by almarti3          #+#    #+#             */
/*   Updated: 2026/03/08 18:25:37 by almarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_param(char *line)
{
	if (!ft_strncmp(line, "NO", 2) && is_space(line[2]))
		return (1);
	if (!ft_strncmp(line, "SO", 2) && is_space(line[2]))
		return (1);
	if (!ft_strncmp(line, "WE", 2) && is_space(line[2]))
		return (1);
	if (!ft_strncmp(line, "EA", 2) && is_space(line[2]))
		return (1);
	if (!ft_strncmp(line, "F", 1) && is_space(line[1]))
		return (1);
	if (!ft_strncmp(line, "C", 1) && is_space(line[1]))
		return (1);
	return (0);
}

void	parse_param(t_game *game, char *line)
{
	if (!ft_strncmp(line, "NO", 2) && is_space(line[2]))
		parse_texture(game, &game->config.no, line + 2);
	else if (!ft_strncmp(line, "SO", 2) && is_space(line[2]))
		parse_texture(game, &game->config.so, line + 2);
	else if (!ft_strncmp(line, "WE", 2) && is_space(line[2]))
		parse_texture(game, &game->config.we, line + 2);
	else if (!ft_strncmp(line, "EA", 2) && is_space(line[2]))
		parse_texture(game, &game->config.ea, line + 2);
	else if (!ft_strncmp(line, "F", 1) && is_space(line[1]))
		parse_color(game, game->config.floor_color, line + 1, 1);
	else if (!ft_strncmp(line, "C", 1) && is_space(line[1]))
		parse_color(game, game->config.ceil_color, line + 1, 2);
	else
		error_exit(game, "Unknown parameter");
}

int	all_params_set(t_config *cfg)
{
	if (!cfg->no || !cfg->so || !cfg->we || !cfg->ea)
		return (0);
	if (cfg->floor_color == -1 || cfg->ceil_color == -1)
		return (0);
	return (1);
}
