NAME    = cub3d
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

LIBFT_DIR = ./libft
LIBFT     = $(LIBFT_DIR)/libft.a

MLX_DIR   = ./minilibx/MLX42
MLX_LIB   = $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS = -lglfw -ldl -pthread -lm

INCLUDES  = -I./includes -I$(LIBFT_DIR) -I$(MLX_DIR)/include

SRC = main.c errors.c free_game.c init_game.c movement.c \
      parsing/parse_cub.c parsing/parse_params.c \
      parsing/parse_textures.c parsing/parse_colors.c \
      parsing/parse_map.c parsing/parse_map_utils.c \
      parsing/map_validation.c parsing/utils.c \
	  rendering/minimap.c rendering/raycasting.c \
      getnextline/get_next_line.c \
	  getnextline/get_next_line_utils.c

OBJ = $(SRC:.c=.o)


all: $(MLX_LIB) $(LIBFT) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX_LIB):
	@cmake -S $(MLX_DIR) -B $(MLX_DIR)/build
	@cmake --build $(MLX_DIR)/build -j4

clean:
	rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(MLX_DIR)/build

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re