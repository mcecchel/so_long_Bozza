/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:01:14 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/27 16:05:58 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* void	initialize_enemies(t_game *game)
{
	int	i;
	int	j;
	int	enemy_index;

	game->collectibles = ft_calloc(game->player.total_collectibles, sizeof(t_collectible));
	if (!game->collectibles)
		error_exit("Error\nMemory allocation failed\n", game);
	i = -1;
	coll_index = 0;
	while (game->map.map[++i] != NULL)
	{
		j = 0;
		while (game->map.map[i][j] != '\0')
		{
			if (game->map.map[i][j] == 'C')
			{
				game->collectibles[coll_index].pos_x = j;
				game->collectibles[coll_index].pos_y = i;
				game->collectibles[coll_index].sprite = get_random_coll_sprite(game);
				game->map.map[i][j] = '0';
				coll_index++;
			}
			j++;
		}
	}
} */

void	initialize_enemies(t_game *game)
{
	int	i;
	int	j;
	int	enemy_index;

	// game->enemies.enemies_count = 0;
	game->enemies = (t_enemy *)ft_calloc(game->enemies.enemies_count, sizeof(t_enemy));
	if (!game->enemies)
		error_exit("Error\nMemory allocation failed\n", game);
	
}