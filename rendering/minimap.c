/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minimap.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: almarti3 <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/03/08 19:32:27 by almarti3		  #+#	#+#			 */
/*   Updated: 2026/03/08 19:32:29 by almarti3		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../cub3d.h"

// Dibuja un cuadrado protegiendo los límites de la pantalla (Evita Segfaults)
static void	draw_square(int x, int y, uint32_t color, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (x + j >= 0 && x + j < WIDTH && y + i >= 0 && y + i < HEIGHT)
				mlx_put_pixel(g_game->frame, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

// Escanea la matriz y dibuja el mapa y al jugador
void	draw_minimap(void)
{
	int	y;
	int	x;
	int	p_size;

	y = 0;
	while (y < g_game->map.height)
	{
		x = 0;
		while (x < g_game->map.width)
		{
			if (g_game->map.grid[y][x] == '1')
				draw_square(x * MM_SCALE, y * MM_SCALE, MM_WALL, MM_SCALE);
			else if (g_game->map.grid[y][x] != ' '
				&& g_game->map.grid[y][x] != '\0')
				draw_square(x * MM_SCALE, y * MM_SCALE, MM_FLOOR, MM_SCALE);
			x++;
		}
		y++;
	}
	p_size = MM_SCALE / 2;
	draw_square((int)(g_game->player.x * MM_SCALE) - (p_size / 2),
		(int)(g_game->player.y * MM_SCALE) - (p_size / 2), MM_PLAYER, p_size);
}

void	draw_background(void)
{
	int	x;
	int	y;
	int	horizon;

	horizon = HEIGHT / 2 + g_game->player.pitch;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < horizon)
				mlx_put_pixel(g_game->frame, x, y, g_game->config.ceil_color);
			else
				mlx_put_pixel(g_game->frame, x, y, g_game->config.floor_color);
			x++;
		}
		y++;
	}
}
