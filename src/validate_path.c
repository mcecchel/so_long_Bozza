/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianna <marianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:59:00 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/02 18:57:44 by marianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player(t_game *game)
{
	int			i;
	int			j;

	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (game->map.map[i][j] != '\0')
		{
			if (game->map.map[i][j] == 'P')
			{
				game->player.px = j;
				game->player.py = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	flood_fill(t_game *game, char **map, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.columns || y >= game->map.rows
		|| map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(game, map, x + 1, y);
	flood_fill(game, map, x - 1, y);
	flood_fill(game, map, x, y + 1);
	flood_fill(game, map, x, y - 1);
}

int	check_reachability(t_game *game, char **map)
{
	int			i;
	int			j;

	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'C' || map[i][j] == 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_path(t_game *game)
{
	int			i;
	char		**map_copy;
	int			reached;

	i = 0;
	find_player(game);
	map_copy = ft_calloc(game->map.rows + 1, sizeof(char *));
	while (i < game->map.rows)
	{
		map_copy[i] = ft_strdup(game->map.map[i]);
		if (!map_copy[i])
			return (free_matrix(map_copy),
				error_exit("Error\nMemory allocation failed\n", game), 0);
		i++;
	}
	flood_fill(game, map_copy, game->player.px, game->player.py);
	//print_matrix(map_copy);
	reached = check_reachability(game, map_copy);
	free_matrix(map_copy);
	return (reached);
}
