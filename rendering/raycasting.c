/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarti3 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 19:31:08 by almarti3          #+#    #+#             */
/*   Updated: 2026/03/08 19:31:09 by almarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	perform_dda(t_game *game, t_ray *r)
{
	while (r->hit == 0)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (game->map.grid[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
	if (r->side == 0)
		r->perp_dist = (r->side_x - r->delta_x);
	else
		r->perp_dist = (r->side_y - r->delta_y);
}

static void	calc_projection(t_game *game, t_ray *r, t_player *p)
{
	if (r->perp_dist < 0.0001)
		r->perp_dist = 0.0001;
	r->line_h = (int)(HEIGHT / r->perp_dist);
	r->draw_start = -r->line_h / 2 + HEIGHT / 2 + p->pitch;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_h / 2 + HEIGHT / 2 + p->pitch;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;
	if (r->side == 0 && r->dir_x > 0)
		r->tex_num = 3;
	else if (r->side == 0 && r->dir_x < 0)
		r->tex_num = 2;
	else if (r->side == 1 && r->dir_y > 0)
		r->tex_num = 1;
	else
		r->tex_num = 0;
	if (r->side == 0)
		r->wall_x = p->y + r->perp_dist * r->dir_y;
	else
		r->wall_x = p->x + r->perp_dist * r->dir_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)game->tex[r->tex_num]->width);
	if ((r->side == 0 && r->dir_x < 0) || (r->side == 1 && r->dir_y > 0))
		r->tex_x = game->tex[r->tex_num]->width - r->tex_x - 1;
}

static void	draw_column(t_game *game, t_ray *r, int x, t_player *p)
{
	mlx_texture_t	*t;
	double			d[2];
	uint32_t		c;
	int				y;
	int				i;

	t = game->tex[r->tex_num];
	d[0] = 1.0 * t->height / r->line_h;
	d[1] = (r->draw_start - p->pitch - HEIGHT / 2.0 + r->line_h / 2.0) * d[0];
	y = r->draw_start;
	while (y <= r->draw_end)
	{
		i = (((int)d[1] & (t->height - 1)) * t->width + r->tex_x) * 4;
		d[1] += d[0];
		c = (t->pixels[i] << 24) | (t->pixels[i + 1] << 16);
		c |= (t->pixels[i + 2] << 8) | t->pixels[i + 3];
		if (r->side == 1)
		{
			c = ((t->pixels[i] / 2) << 24) | ((t->pixels[i + 1] / 2) << 16);
			c |= ((t->pixels[i + 2] / 2) << 8) | t->pixels[i + 3];
		}
		mlx_put_pixel(game->frame, x, y, c);
		y++;
	}
}

void	game_loop(void *param)
{
	t_ray		r;
	t_player	*p;
	int			x;
	t_game		*game;

	game = (t_game *)param;
	handle_movement(game);
	p = &game->player;
	draw_background(game);
	x = 0;
	while (x < WIDTH)
	{
		init_ray(&r, p, x);
		perform_dda(game, &r);
		calc_projection(game, &r, p);
		draw_column(game, &r, x, p);
		x++;
	}
	draw_minimap(game);
}
