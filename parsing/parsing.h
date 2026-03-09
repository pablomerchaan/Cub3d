/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarti3 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:26:21 by almarti3          #+#    #+#             */
/*   Updated: 2026/03/08 18:26:22 by almarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../cub3d.h"

int		is_space(char s);
int		is_param(char *line);
void	parse_param(t_game *game, char *line);
int		all_params_set(t_config *cfg);
void	parse_texture(t_game *game, char **dst, char *str);
void	parse_color(t_game *game, int dst, char *str, int sw);
void	append_map_line(t_game *game, t_map *map, char *line);
void	make_map_rectangular(t_map *map);
void	parse_player(t_game *game, t_map *map, t_player *player);
void	validate_map(t_game *game, t_map *map);
int		is_empty(char *line);
int		count_args(char **arr);
void	free_split(char **arr);
int		find_longest_line(t_map *map);
char	*pad_with_spaces(char *line, int length);
void	init_player_direction(t_player *player, char dir);
t_game	*container_of(t_game *game);
#endif
