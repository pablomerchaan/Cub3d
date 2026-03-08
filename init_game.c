#include "cub3d.h"

static void load_textures(void)
{
    g_game->tex[0] = mlx_load_png(g_game->config.no);
    if (!g_game->tex[0]) error_exit("Failed to load NO texture");

    g_game->tex[1] = mlx_load_png(g_game->config.so);
    if (!g_game->tex[1]) error_exit("Failed to load SO texture");

    g_game->tex[2] = mlx_load_png(g_game->config.we);
    if (!g_game->tex[2]) error_exit("Failed to load WE texture");

    g_game->tex[3] = mlx_load_png(g_game->config.ea);
    if (!g_game->tex[3]) error_exit("Failed to load EA texture");
}

void    init_game(void)
{
    for (int i = 0; i < 4; i++)
        g_game->tex[i] = NULL;

    g_game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D - Bonus", true);
    if (!g_game->mlx)
        error_exit("MLX42 init failed");
    mlx_set_cursor_mode(g_game->mlx, MLX_MOUSE_HIDDEN);

    g_game->frame = mlx_new_image(g_game->mlx, WIDTH, HEIGHT);
    if (!g_game->frame)
        error_exit("Frame creation failed");

    if (mlx_image_to_window(g_game->mlx, g_game->frame, 0, 0) < 0)
        error_exit("Window connection failed");

    // 1. CARGAMOS TEXTURAS DEL ENTORNO PRIMERO (Seguridad de memoria)
    load_textures();

    // 2. INYECCIÓN DEL ARMA (Sin escalado dinámico)
    mlx_texture_t *tex_idle = mlx_load_png("textures/gun.png");
    mlx_texture_t *tex_fire = mlx_load_png("textures/gun_fire.png");
    if (!tex_idle || !tex_fire) error_exit("Failed to load weapon textures");
    
    g_game->gun_idle = mlx_texture_to_image(g_game->mlx, tex_idle);
    g_game->gun_fire = mlx_texture_to_image(g_game->mlx, tex_fire);
    mlx_delete_texture(tex_idle);
    mlx_delete_texture(tex_fire);
    
    int gun_x = (WIDTH / 2) - (g_game->gun_idle->width / 2) + 200;
    int gun_y = HEIGHT - g_game->gun_idle->height;
    
    if (mlx_image_to_window(g_game->mlx, g_game->gun_idle, gun_x, gun_y) < 0 ||
        mlx_image_to_window(g_game->mlx, g_game->gun_fire, gun_x, gun_y) < 0)
        error_exit("Weapon connection failed");

    // Inicializar estado: Reposo encendido, Disparo apagado
    g_game->gun_idle->instances[0].enabled = true;
    g_game->gun_fire->instances[0].enabled = false;
    g_game->shoot_counter = 0;
}