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

t_game	*g_game = NULL;

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

static void	init_struct(void)
{
	g_game->config.floor_color = -1;
	g_game->config.ceil_color = -1;
	g_game->config.no = NULL;
	g_game->config.so = NULL;
	g_game->config.we = NULL;
	g_game->config.ea = NULL;
	g_game->map.grid = NULL;
	g_game->map.width = 0;
	g_game->map.height = 0;
	g_game->mlx = NULL;
	g_game->frame = NULL;
	g_game->player.pitch = 0;
}

int	main(int argc, char **argv)
{
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
	g_game = malloc(sizeof(t_game));
	if (!g_game)
		return (1);
	init_struct();
	parse_cub(argv[1]);
	init_game();
	mlx_loop_hook(g_game->mlx, game_loop, NULL);
	mlx_loop(g_game->mlx);
	mlx_terminate(g_game->mlx);
	free_game();
	free(g_game);
	return (0);
}
