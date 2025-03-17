/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:29:06 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/17 15:43:38 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	validate_file(const char *filename)
{
	if (!has_ber_extension(filename))
		file_error_exit("Error\nInvalid file extension\n");
	else if (!file_exists(filename))
		file_error_exit("Error\nFile does not exist\n");
	else if (is_folder(filename))
		file_error_exit("Error\nFile is a directory\n");
	else if (!is_readable(filename))
		file_error_exit("Error\nFile is not readable\n");
	else
		return ;
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
	reached = check_reachability(game, map_copy);
	free_matrix(map_copy);
	return (reached);
}

void	initialize_game(t_game *game, void *mlx, void *mlx_win)
{
	get_other_sprite(game);
	get_player_sprite(game);
	game->player.sprite = game->sprites.player.front;
	get_coll_sprite(game);
	get_enemy_sprite(game);
	initialize_collectibles(game);
	initialize_enemies(game);
	draw_map(game, mlx, mlx_win);
}
