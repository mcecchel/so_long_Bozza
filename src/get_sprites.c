/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:46:33 by marianna          #+#    #+#             */
/*   Updated: 2025/03/12 17:54:29 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_player_sprite(t_game *game)
{
	int width;
	int height;

	game->sprites.player.front = mlx_xpm_file_to_image(game->window.mlx, "./textures/front.xpm", &width, &height);
	game->sprites.player.back = mlx_xpm_file_to_image(game->window.mlx, "./textures/back.xpm", &width, &height);
	game->sprites.player.right = mlx_xpm_file_to_image(game->window.mlx, "./textures/right.xpm", &width, &height);
	game->sprites.player.left = mlx_xpm_file_to_image(game->window.mlx, "./textures/left.xpm", &width, &height);
	if (!game->sprites.player.front || !game->sprites.player.back || !game->sprites.player.right || !game->sprites.player.left)
	{
		printf("Error\nFailed to load player sprite\n");
		free_resources(game);
		exit(1);
	}
}

void	get_coll_sprite(t_game *game)
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

void	get_enemy_sprite(t_game *game)
{
	int width;
	int height;

	game->sprites.enemy.dx = mlx_xpm_file_to_image(game->window.mlx, "./textures/enemy_dx.xpm", &width, &height);
	game->sprites.enemy.sx = mlx_xpm_file_to_image(game->window.mlx, "./textures/enemy_sx.xpm", &width, &height);
	if (!game->sprites.enemy.dx || !game->sprites.enemy.sx)
	{
		printf("Error\nFailed to load enemy sprite\n");
		free_resources(game);
		exit(1);
	}
}

void	get_other_sprite(t_game *game)
{
	int width;
	int height;

	game->sprites.wall = mlx_xpm_file_to_image(game->window.mlx, "./textures/wall.xpm", &width, &height);
	game->sprites.floor = mlx_xpm_file_to_image(game->window.mlx, "./textures/floor.xpm", &width, &height);
	game->sprites.exit = mlx_xpm_file_to_image(game->window.mlx, "./textures/exit.xpm", &width, &height);
	// player sprites
	game->sprites.moves_background = mlx_xpm_file_to_image(game->window.mlx, "./textures/sus.xpm", &width, &height);
	if (!game->sprites.wall || !game->sprites.floor || !game->sprites.exit || !game->sprites.moves_background)
	{
		printf("Error\nFailed to load textures\n");
		free_resources(game);
		exit(1);
	}
}
