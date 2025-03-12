/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:21:44 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/12 18:10:21 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_char_sprites(t_game *game, void *mlx)
{
	if (game->sprites.player.front)
		mlx_destroy_image(mlx, game->sprites.player.front);
	if (game->sprites.player.back)
		mlx_destroy_image(mlx, game->sprites.player.back);
	if (game->sprites.player.right)
		mlx_destroy_image(mlx, game->sprites.player.right);
	if (game->sprites.player.left)
		mlx_destroy_image(mlx, game->sprites.player.left);
	if (game->sprites.enemy.dx)
		mlx_destroy_image(mlx, game->sprites.enemy.dx);
	if (game->sprites.enemy.sx)
		mlx_destroy_image(mlx, game->sprites.enemy.sx);
}

void	destroy_static_sprites(t_game *game, void *mlx)
{
	if (game->sprites.wall)
		mlx_destroy_image(mlx, game->sprites.wall);
	if (game->sprites.floor)
		mlx_destroy_image(mlx, game->sprites.floor);
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
	if (game->sprites.moves_background)
		mlx_destroy_image(mlx, game->sprites.moves_background);
}

void	destroy_sprites(t_game *game, void *mlx)
{
	destroy_char_sprites(game, mlx);
	destroy_static_sprites(game, mlx);
}

void	free_resources(t_game *game)
{
	destroy_sprites(game, game->window.mlx);
	free_matrix(game->map.map);
	if (game->window.mlx_win)
		mlx_destroy_window(game->window.mlx, game->window.mlx_win);
	mlx_destroy_display(game->window.mlx);
	free(game->collectibles);
	free(game->enemies);
	free(game->window.mlx);
}

int	close_game(t_game *game)
{
	free_resources(game);
	exit(0);
	return (0);
}
