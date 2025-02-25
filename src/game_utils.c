/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:21:44 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/25 18:35:54 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Map utils
void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix != NULL && matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

// Free & exit game
void	destroy_sprites(t_game *game, void *mlx)
{
	if (game->sprites.wall)
		mlx_destroy_image(mlx, game->sprites.wall);
	if (game->sprites.floor)
		mlx_destroy_image(mlx, game->sprites.floor);
	if (game->sprites.player)
		mlx_destroy_image(mlx, game->sprites.player);
	if (game->sprites.coll1 && game->sprites.coll2 && game->sprites.coll3 && game->sprites.coll4)
	{
		mlx_destroy_image(mlx, game->sprites.coll1);
		mlx_destroy_image(mlx, game->sprites.coll2);
		mlx_destroy_image(mlx, game->sprites.coll3);
		mlx_destroy_image(mlx, game->sprites.coll4);
	}
	if (game->sprites.exit)
		mlx_destroy_image(mlx, game->sprites.exit);
}

void	free_resources(t_game *game)
{
	destroy_sprites(game, game->window.mlx);
	free_matrix(game->map.map);
	mlx_destroy_window(game->window.mlx, game->window.mlx_win);
	mlx_destroy_display(game->window.mlx);
	free(game->window.mlx);
}

int	close_game(t_game *game)
{
	free_resources(game);
	exit(0);
	return (0);
}
