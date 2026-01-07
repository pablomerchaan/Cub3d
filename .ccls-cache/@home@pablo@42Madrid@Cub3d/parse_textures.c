#include "parsing.h"

static int	has_xpm_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (!ft_strncmp(path + len - 4, ".xpm", 4));
}

static char	*extract_path(char *str)
{
	char	*path;

	path = ft_strtrim(str, " \t\n");
	if (!path || path[0] == '\0')
		error_exit("Invalid texture path");
	return (path);
}

static void	check_texture_file(char *path)
{
	int	fd;

	if (!has_xpm_extension(path))
		error_exit("Texture must be .xpm");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Texture file cannot be opened");
	close(fd);
}

void	parse_texture(char **dst, char *str)
{
	char	*path;

	if (*dst != NULL)
		error_exit("Duplicate texture");

	path = extract_path(str);
	check_texture_file(path);
	*dst = path;
}
