/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:57:35 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/09 17:59:54 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_rectangular(t_game *game)
{
	int	i;

	i = 1;
	game->map.columns = ft_strlen(game->map.map[0]);
	while (i < game->map.rows)
	{
		if ((int)ft_strlen(game->map.map[i]) != game->map.columns)
		{
			error_exit("Error\nMap is not rectangular\n", game);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_map_borders(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.columns)
	{
		if (game->map.map[0][i] != '1'
			|| game->map.map[game->map.rows - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < game->map.rows)
	{
		if (game->map.map[i][0] != '1'
			|| game->map.map[i][game->map.columns - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

void	count_map_elements(t_game *game, int i, int j)
{
	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.columns && game->map.map[i][j])
		{
			if (game->map.map[i][j] == 'P')
			{
				game->player.px = j;
				game->player.py = i;
				game->parse.player++;
			}
			else if (game->map.map[i][j] == 'C')
				game->parse.collectible++;
			else if (game->map.map[i][j] == 'N')
				game->player.total_enemies++;
			else if (game->map.map[i][j] == 'E')
				game->parse.exit_game++;
			else if (game->map.map[i][j] != '1' && game->map.map[i][j] != '0')
				return ;
			j++;
		}
		i++;
	}
}

int	check_map_elements(t_game *game)
{
	count_map_elements(game, 0, 0);
	if (game->parse.player != 1 || game->parse.exit_game != 1
		|| game->parse.collectible < 1)
	{
		error_exit("Error\nInvalid map element\n", game);
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!is_rectangular(game))
		return (0);
	if (!check_map_borders(game))
		return (0);
	if (!check_map_elements(game))
		return (0);
	return (1);
}
