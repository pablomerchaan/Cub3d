#include "parsing/parsing.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf("Usage: %s map.cub\n", av[0]);
		return (1);
	}
	init_game(&game);
	parse_cub(av[1], &game);
	printf("Parsing OK ✅\n");
	free_game();
	return (0);
}
