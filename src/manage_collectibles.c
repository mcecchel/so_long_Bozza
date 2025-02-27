/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_collectibles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:19:19 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/27 15:24:09 by mcecchel         ###   ########.fr       */
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

void	initialize_collectibles(t_game *game)
{
	int	i;
	int	j;
	int	coll_index;

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
}

void	init_coll_sprite(t_game *game)
{
	int width;
	int height;

	game->sprites.collectible.coll1 = mlx_xpm_file_to_image(game->window.mlx, "./textures/coll1.xpm", &width, &height);
	game->sprites.collectible.coll2 = mlx_xpm_file_to_image(game->window.mlx, "./textures/coll2.xpm", &width, &height);
	game->sprites.collectible.coll3 = mlx_xpm_file_to_image(game->window.mlx, "./textures/coll3.xpm", &width, &height);
	game->sprites.collectible.coll4 = mlx_xpm_file_to_image(game->window.mlx, "./textures/coll4.xpm", &width, &height);
	if (!game->sprites.collectible.coll1 || !game->sprites.collectible.coll2 || !game->sprites.collectible.coll3 || !game->sprites.collectible.coll4)
	{
		printf("Error\nFailed to load collectible sprite\n");
		free_resources(game);
		exit(1);
	}
}

void	draw_collectibles(t_game *game)
{
	int				i;
	t_collectible	coll;

	i = 0;
	while (i < game->player.total_collectibles)
	{
		coll = game->collectibles[i];
		if (coll.sprite)
			mlx_put_image_to_window(game->window.mlx, game->window.mlx_win, coll.sprite, coll.pos_x * TILE_SIZE, coll.pos_y * TILE_SIZE);
		i++;
	}
}

t_collectible *is_collectible(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->player.total_collectibles)
	{
		if (game->collectibles[i].pos_x == x && game->collectibles[i].pos_y == y)
			return (&game->collectibles[i]);
		i++;
	}
	return (NULL);
}
