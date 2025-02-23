/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_collectibles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:51:36 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/23 16:16:16 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* void	find_player(t_game *game, int *pos_x, int *pos_y)
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
				*pos_x = j;
				*pos_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
} */
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

void	randomize_coll_sprite(t_game *game)
{
	int	random_index;
	char *coll_sprites[4] =
	{
		"./textures/coll1.xpm"
		"./textures/coll2.xpm"
		"./textures/coll3.xpm"
		"./textures/coll4.xpm"
	};
	srand(time(NULL));
	random_index = rand() % 4;
	game->sprites.collectible = mlx_xpm_file_to_image(game->window.mlx, coll_sprites[random_index], &game->window.img_width, &game->window.img_height);
	if (!game->sprites.collectible)
		error_exit("Error\nFailed to load collectible sprite\n", game);
}

bool	all_collected(t_game *game)
{
	if (game->player.collected_items == game->player.total_collectibles)
		return (true);
	return (false);
}
