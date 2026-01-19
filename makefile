NAME	= cub3d

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g

LIBFT	= libft/libft.a
MLX		= mlx/libmlx42.a

INCLUDES = -Iincludes -Ilibft -Imlx/include

SRC = \
	main.c \
	errors.c \
	free_game.c \
	parsing/parse_cub.c \
	parsing/parse_params.c \
	parsing/parse_textures.c \
	parsing/parse_colors.c \
	parsing/parse_map.c \
	parsing/parse_map_utils.c \
	parsing/map_validation.c \
	getnextline/get_next_line.c \
	parsing/utils.c \
	init_game.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

$(LIBFT):
	make -C libft

$(MLX):
	make -C mlx

clean:
	rm -f $(OBJ)
	make -C libft clean
	make -C mlx clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
