/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_collectibles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:19:19 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/21 14:59:31 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_single_collectible(t_game *game, int i, int j, int *coll_index)
{
	game->collectibles[*coll_index].pos_x = j;
	game->collectibles[*coll_index].pos_y = i;
	game->collectibles[*coll_index].sprite = get_random_coll_sprite(game);
	game->map.map[i][j] = '0';
	(*coll_index)++;
}

void	initialize_collectibles(t_game *game)
{
	int	i;
	int	j;
	int	coll_index;

	game->collectibles = ft_calloc(game->parse.total_collectibles,
			sizeof(t_coll));
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
				init_single_collectible(game, i, j, &coll_index);
			j++;
		}
	}
}

t_coll	*is_collectible(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->parse.total_collectibles)
	{
		if (game->collectibles[i].pos_x == x
			&& game->collectibles[i].pos_y == y)
			return (&game->collectibles[i]);
		i++;
	}
	return (NULL);
}

bool	all_collected(t_game *game)
{
	if (game->player.collected_items == game->parse.total_collectibles)
		return (true);
	return (false);
}
