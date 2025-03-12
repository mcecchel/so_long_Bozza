/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomize_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:23:56 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/12 19:25:07 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*get_random_coll_sprite(t_game *game)
{
	int	random_sprite;

	random_sprite = rand() % 4;
	if (random_sprite == 0)
		return (game->sprites.collectible.coll1);
	else if (random_sprite == 1)
		return (game->sprites.collectible.coll2);
	else if (random_sprite == 2)
		return (game->sprites.collectible.coll3);
	else
		return (game->sprites.collectible.coll4);
}

void	*get_random_enemy_sprite(t_game *game)
{
	int	random_sprite;

	random_sprite = rand() % 2;
	if (random_sprite == 0)
		return (game->sprites.enemy.dx);
	else
		return (game->sprites.enemy.sx);
}
