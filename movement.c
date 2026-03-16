/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarti3 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 19:54:05 by almarti3          #+#    #+#             */
/*   Updated: 2026/03/08 19:54:08 by almarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_player *p, double rot_dir)
{
	double	old_dir;
	double	old_plane;
	double	rot;

	old_dir = p->dir_x;
	old_plane = p->plane_x;
	rot = ROT_SPEED * rot_dir;
	p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
	p->dir_y = old_dir * sin(rot) + p->dir_y * cos(rot);
	p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
	p->plane_y = old_plane * sin(rot) + p->plane_y * cos(rot);
}

static void	move_axis(t_player *p, char **grid, double dir_x, double dir_y)
{
	if (grid[(int)p->y][(int)(p->x + dir_x * MOVE_SPEED)] != '1')
		p->x += dir_x * MOVE_SPEED;
	if (grid[(int)(p->y + dir_y * MOVE_SPEED)][(int)p->x] != '1')
		p->y += dir_y * MOVE_SPEED;
}

static void	handle_translation(t_game *game, t_player *p, char **grid)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_axis(p, grid, p->dir_x, p->dir_y);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_axis(p, grid, -p->dir_x, -p->dir_y);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_axis(p, grid, -p->dir_y, p->dir_x);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_axis(p, grid, p->dir_y, -p->dir_x);
}

static void	handle_actions(t_game *game, t_player *p)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		p->pitch += 15;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		p->pitch -= 15;
	if (p->pitch > 300)
		p->pitch = 300;
	if (p->pitch < -300)
		p->pitch = -300;
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE)
		|| mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT)
		|| mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_RIGHT))
		if (game->shoot_counter == 0)
			game->shoot_counter = 5;
	if (game->shoot_counter > 0)
	{
		game->gun_idle->instances[0].enabled = false;
		game->gun_fire->instances[0].enabled = true;
		game->shoot_counter--;
	}
	else
	{
		game->gun_idle->instances[0].enabled = true;
		game->gun_fire->instances[0].enabled = false;
	}
}

static void handle_mouse_rot(t_game *game, t_player *p)
{
	static int m_key_lock = 0;
	int	x;
	int	y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_M) && !m_key_lock)
	{
		game->mouse_toggle = !game->mouse_toggle;
		m_key_lock = 1;
		if (game->mouse_toggle)
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
		else
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
	}
	else if (!mlx_is_key_down(game->mlx, MLX_KEY_M))
		m_key_lock = 0;
	if (game->mouse_toggle)
	{
		mlx_get_mouse_pos(game->mlx, &x, &y);
		if (x != WIDTH / 2 || y != HEIGHT / 2)
		{
			rotate_player(p, ((x - (WIDTH / 2)) * 0.003) / ROT_SPEED);
			p->pitch -= (y - (HEIGHT / 2));
			mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
		}
	}
}

void	handle_movement(t_game *game)
{
	t_player	*p;

	p = &game->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(p, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(p, -1);
	handle_mouse_rot(game, p);
	handle_translation(game, p, game->map.grid);
	handle_actions(game, p);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}
