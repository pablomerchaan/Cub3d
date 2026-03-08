#include "cub3d.h"

#define MOVE_SPEED 0.05
#define ROT_SPEED 0.03

static void rotate_player(t_player *p, double rot_dir)
{
    double old_dir_x;
    double old_plane_x;
    double rot;

    old_dir_x = p->dir_x;
    old_plane_x = p->plane_x;
    rot = ROT_SPEED * rot_dir;

    // Rotar el vector de dirección
    p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
    p->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);

    // Rotar el plano de la cámara (FOV)
    p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
    p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
}

static void handle_movement(void)
{
    t_player    *p = &g_game->player;
    char        **grid = g_game->map.grid;

    // Rotación (Flechas Izquierda/Derecha)
    if (mlx_is_key_down(g_game->mlx, MLX_KEY_RIGHT))
        rotate_player(p, 1);
    if (mlx_is_key_down(g_game->mlx, MLX_KEY_LEFT))
        rotate_player(p, -1);


    // --- CONTROL DE RATÓN ---
    int mouse_x;
    int mouse_y;
    mlx_get_mouse_pos(g_game->mlx, &mouse_x, &mouse_y);
    
    // Si el ratón se ha movido del centro (WIDTH / 2)
    if (mouse_x != WIDTH / 2)
    {
        double rotation = (mouse_x - (WIDTH / 2)) * 0.003; // 0.003 es la sensibilidad
        rotate_player(p, rotation / ROT_SPEED); // Reutilizamos tu propia función
        
        // Forzar el ratón de vuelta al centro para evitar que salga de la ventana
        mlx_set_mouse_pos(g_game->mlx, WIDTH / 2, HEIGHT / 2);
    }


    // Avance (W)
    if (mlx_is_key_down(g_game->mlx, MLX_KEY_W))
    {
        if (grid[(int)p->y][(int)(p->x + p->dir_x * MOVE_SPEED)] != '1')
            p->x += p->dir_x * MOVE_SPEED;
        if (grid[(int)(p->y + p->dir_y * MOVE_SPEED)][(int)p->x] != '1')
            p->y += p->dir_y * MOVE_SPEED;
    }
    
    // Retroceso (S)
    if (mlx_is_key_down(g_game->mlx, MLX_KEY_S))
    {
        if (grid[(int)p->y][(int)(p->x - p->dir_x * MOVE_SPEED)] != '1')
            p->x -= p->dir_x * MOVE_SPEED;
        if (grid[(int)(p->y - p->dir_y * MOVE_SPEED)][(int)p->x] != '1')
            p->y -= p->dir_y * MOVE_SPEED;
    }

    // Desplazamiento lateral derecho (D)
    if (mlx_is_key_down(g_game->mlx, MLX_KEY_D))
    {
        double perp_x = -p->dir_y;
        double perp_y = p->dir_x;
        if (grid[(int)p->y][(int)(p->x + perp_x * MOVE_SPEED)] != '1')
            p->x += perp_x * MOVE_SPEED;
        if (grid[(int)(p->y + perp_y * MOVE_SPEED)][(int)p->x] != '1')
            p->y += perp_y * MOVE_SPEED;
    }

    // Desplazamiento lateral izquierdo (A)
    if (mlx_is_key_down(g_game->mlx, MLX_KEY_A))
    {
        double perp_x = p->dir_y;
        double perp_y = -p->dir_x;
        if (grid[(int)p->y][(int)(p->x + perp_x * MOVE_SPEED)] != '1')
            p->x += perp_x * MOVE_SPEED;
        if (grid[(int)(p->y + perp_y * MOVE_SPEED)][(int)p->x] != '1')
            p->y += perp_y * MOVE_SPEED;
    }
    // Mirar Arriba / Abajo (Pitch)
    if (mlx_is_key_down(g_game->mlx, MLX_KEY_UP))
        p->pitch += 15;
    if (mlx_is_key_down(g_game->mlx, MLX_KEY_DOWN))
        p->pitch -= 15;
    if (p->pitch > 300) p->pitch = 300;
    if (p->pitch < -300) p->pitch = -300;

    // Gatillo (Barra Espaciadora)
    if (mlx_is_key_down(g_game->mlx, MLX_KEY_SPACE))
    {
        // Solo dispara si no está disparando ya
        if (g_game->shoot_counter == 0)
            g_game->shoot_counter = 5; // Mantendrá el fogonazo durante 5 frames
    }

    // Lógica de Animación
    if (g_game->shoot_counter > 0)
    {
        g_game->gun_idle->instances[0].enabled = false;
        g_game->gun_fire->instances[0].enabled = true;
        g_game->shoot_counter--; // Cuenta atrás
    }
    else
    {
        g_game->gun_idle->instances[0].enabled = true;
        g_game->gun_fire->instances[0].enabled = false;
    }
    
    // Botón de escape para cerrar limpio
    if (mlx_is_key_down(g_game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(g_game->mlx);
}


// // Función auxiliar para pintar una línea vertical rápida
// static void draw_vert_line(int x, int draw_start, int draw_end, uint32_t color)
// {
//     int y;

//     y = draw_start;
//     while (y <= draw_end)
//     {
//         mlx_put_pixel(g_game->frame, x, y, color);
//         y++;
//     }
// }

// Pintar el fondo (Suelo y Techo)
static void draw_background(void)
{
    int x;
    int y;
    int horizon = HEIGHT / 2 + g_game->player.pitch;

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

// El motor matemático puro
void game_loop(void *param)
{
    t_player *p;
    int x;

    (void)param;
    handle_movement();
    p = &g_game->player;
    draw_background();

    x = 0;
    while (x < WIDTH)
    {
        // 1. Vectores del Rayo
        double camera_x = 2 * x / (double)WIDTH - 1;
        double ray_dir_x = p->dir_x + p->plane_x * camera_x;
        double ray_dir_y = p->dir_y + p->plane_y * camera_x;

        // 2. Coordenadas de la matriz 2D
        int map_x = (int)p->x;
        int map_y = (int)p->y;

        // 3. Variables del DDA
        double side_dist_x;
        double side_dist_y;
        double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
        double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

        int step_x;
        int step_y;
        int hit = 0;
        int side = 0;

        // 4. Calcular el paso inicial y la distancia lateral
        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (p->x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - p->x) * delta_dist_x;
        }
        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (p->y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - p->y) * delta_dist_y;
        }

        // 5. Ejecutar el DDA (Saltar por la cuadrícula)
        while (hit == 0)
        {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            // Si tocamos un muro '1', el rayo se detiene
            if (g_game->map.grid[map_y][map_x] == '1')
                hit = 1;
        }

        // 6. Proyección: Evitar el Ojo de Pez y calcular altura
        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = (side_dist_x - delta_dist_x);
        else
            perp_wall_dist = (side_dist_y - delta_dist_y);

        int line_height = (int)(HEIGHT / perp_wall_dist);

        // 7. Calcular límites de dibujo en pantalla
        int draw_start = -line_height / 2 + HEIGHT / 2 + p->pitch;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + HEIGHT / 2 + p->pitch;
        if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

        // --- NUEVA FASE: MAPEADO DE TEXTURAS ---

        // A. Determinar qué textura usar (Norte, Sur, Este, Oeste)
        int tex_num;
        if (side == 0 && ray_dir_x > 0) tex_num = 3;      // Este
        else if (side == 0 && ray_dir_x < 0) tex_num = 2; // Oeste
        else if (side == 1 && ray_dir_y > 0) tex_num = 1; // Sur
        else tex_num = 0;                                 // Norte

        mlx_texture_t *tex = g_game->tex[tex_num];

        // B. Calcular en qué punto exacto de la pared golpeó el rayo (wall_x)
        double wall_x;
        if (side == 0) wall_x = p->y + perp_wall_dist * ray_dir_y;
        else           wall_x = p->x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);

        // C. Calcular la coordenada X en la textura (tex_x)
        int tex_x = (int)(wall_x * (double)tex->width);
        if (side == 0 && ray_dir_x > 0) tex_x = tex->width - tex_x - 1;
        if (side == 1 && ray_dir_y < 0) tex_x = tex->width - tex_x - 1;

        // D. Preparar el escalado vertical (Paso a paso por los píxeles de la textura)
        double step = 1.0 * tex->height / line_height;
        double tex_pos = (draw_start - p->pitch - HEIGHT / 2.0 + line_height / 2.0) * step;
        // E. Dibujar la línea vertical píxel a píxel
        int y = draw_start;
        while (y <= draw_end)
        {
            int tex_y = (int)tex_pos & (tex->height - 1);
            tex_pos += step;

            // Extraer el color del píxel exacto de la textura
            uint32_t pixel_index = (tex_y * tex->width + tex_x) * tex->bytes_per_pixel;
            uint8_t r = tex->pixels[pixel_index];
            uint8_t g = tex->pixels[pixel_index + 1];
            uint8_t b = tex->pixels[pixel_index + 2];
            uint8_t a = tex->pixels[pixel_index + 3];
            
            // Reconstruir el color para MLX42 (RGBA)
            uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;

            // Opcional: Oscurecer un poco los muros Norte/Sur para dar efecto de sombra 3D
            if (side == 1) 
                color = ((r/2) << 24) | ((g/2) << 16) | ((b/2) << 8) | a;

            mlx_put_pixel(g_game->frame, x, y, color);
            y++;
        }

        x++;
    }
}