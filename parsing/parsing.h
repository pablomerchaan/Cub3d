#ifndef PARSING_H
#define PARSING_H

#include "../cub3d.h"

int		is_param(char *line);
void	parse_param(char *line, t_game *game);
int		all_params_set(t_config *cfg);
void	parse_texture(char **dst, char *str);
void	parse_color(int *dst, char *str);
void	append_map_line(t_map *map, char *line);
void	make_map_rectangular(t_map *map);
void	parse_player(t_map *map, t_player *player);
void	validate_map(t_map *map);
int		is_empty(char *line);
int		count_args(char **arr);
void	free_split(char **arr);

#endif
