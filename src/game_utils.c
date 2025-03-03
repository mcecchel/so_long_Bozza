/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianna <marianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:21:44 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/03 15:53:49 by marianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Map utils
void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix != NULL && matrix[i] != NULL)
	{
		ft_printf("%s\n", matrix[i]);
		i++;
	}
}

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
	if (game->sprites.collectible.coll1)
		mlx_destroy_image(mlx, game->sprites.collectible.coll1);
	if (game->sprites.collectible.coll2)
		mlx_destroy_image(mlx, game->sprites.collectible.coll2);
	if (game->sprites.collectible.coll3)
		mlx_destroy_image(mlx, game->sprites.collectible.coll3);
	if (game->sprites.collectible.coll4)
		mlx_destroy_image(mlx, game->sprites.collectible.coll4);
	if (game->sprites.exit)
		mlx_destroy_image(mlx, game->sprites.exit);
}

void	free_resources(t_game *game)
{
	destroy_sprites(game, game->window.mlx);
	free_matrix(game->map.map);
	mlx_destroy_window(game->window.mlx, game->window.mlx_win);
	mlx_destroy_display(game->window.mlx);
	free(game->collectibles);
	free(game->window.mlx);
}

int	close_game(t_game *game)
{
	free_resources(game);
	exit(0);
	return (0);
}
