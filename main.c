/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: almarti3 <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/03/08 19:32:15 by almarti3		  #+#	#+#			 */
/*   Updated: 2026/03/08 19:32:16 by almarti3		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

static int	check_extension(char *file, char *ext)
{
	int	len_file;
	int	len_ext;

	len_file = ft_strlen(file);
	len_ext = ft_strlen(ext);
	if (len_file <= len_ext)
		return (0);
	if (ft_strncmp(file + len_file - len_ext, ext, len_ext) != 0)
		return (0);
	return (1);
}

static void	init_struct(t_game *game)
{
	game->config.floor_color = -1;
	game->config.ceil_color = -1;
	game->config.no = NULL;
	game->config.so = NULL;
	game->config.we = NULL;
	game->config.ea = NULL;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->mlx = NULL;
	game->frame = NULL;
	game->player.pitch = 0;
}

int	main(int argc, char **argv)
{
	t_game *game;
	if (argc != 2)
	{
		printf("Error\nUsage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	if (!check_extension(argv[1], ".cub"))
	{
		printf("Error\nMap file must have a .cub extension\n");
		return (1);
	}
	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	init_struct(game);
	parse_cub(game, argv[1]);
	init_game(game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_game(game);
	free(game);
	return (0);
}
