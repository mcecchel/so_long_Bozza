/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:45:30 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/21 14:35:32 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(const char *filename)
{
	int		fd;
	char	*line;
	int		lines;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		file_error_exit("Error\nFailed to open file\n");
	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

char	**load_map(const char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		file_error_exit("Error\nFailed to open file\n");
	game->map.rows = count_lines(filename);
	if (game->map.rows <= 0)
		file_error_exit("Error\nEmpty or non-valid file\n");
	game->map.map = ft_calloc(game->map.rows + 1, sizeof(char *));
	if (!game->map.map)
		file_error_exit("Error\nMemory allocation failed\n");
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		game->map.map[i] = ft_strdup(line);
		if (game->map.map[i][ft_strlen(line) - 1] == '\n')
			game->map.map[i][ft_strlen(line) - 1] = '\0';
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (close(fd), game->map.map);
}

char	**read_map(const char *filename, t_game *game)
{
	validate_file(filename);
	game->map.map = load_map(filename, game);
	if (!validate_map(game))
	{
		free_matrix(game->map.map);
		file_error_exit("Error\nInvalid map\n");
	}
	if (!validate_path(game))
		error_exit("Error\nInvalid path\n", game);
	return (game->map.map);
}
