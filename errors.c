#include "parsing.h"

static void	put_error(char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
}

void	error_exit(char *msg)
{
	put_error(msg);
	free_game();
	exit(EXIT_FAILURE);
}
