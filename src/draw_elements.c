/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:05:46 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/21 14:59:31 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "so_long.h"

void	draw_tile(t_game *game, int i, int j)
{
	if (game->map.map[i][j] == '1')
		mlx_put_image_to_window(game->window.mlx, game->window.mlx_win,
			game->sprites.wall, j * TILE_SIZE, i * TILE_SIZE);
	else if (game->map.map[i][j] == '0')
		mlx_put_image_to_window(game->window.mlx, game->window.mlx_win,
			game->sprites.floor, j * TILE_SIZE, i * TILE_SIZE);
	else if (game->map.map[i][j] == 'E')
		mlx_put_image_to_window(game->window.mlx, game->window.mlx_win,
			game->sprites.exit, j * TILE_SIZE, i * TILE_SIZE);
}

void	draw_player(t_game *game, void *mlx, void *mlx_win)
{
	mlx_put_image_to_window(mlx, mlx_win, game->player.sprite,
		game->player.px * TILE_SIZE, game->player.py * TILE_SIZE);
}

void	draw_map(t_game *game, void *mlx, void *mlx_win)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.map[i] != NULL)
	{
		j = 0;
		while (game->map.map[i][j] != '\0')
		{
			draw_tile(game, i, j);
			j++;
		}
		i++;
	}
	draw_collectibles(game);
	draw_player(game, mlx, mlx_win);
	draw_enemies(game);
	show_moves(game);
}

void	draw_collectibles(t_game *game)
{
	int				i;
	t_coll	coll;

	i = 0;
	while (i < game->parse.total_collectibles)
	{
		coll = game->collectibles[i];
		if (coll.sprite)
			mlx_put_image_to_window(game->window.mlx, game->window.mlx_win,
				coll.sprite, coll.pos_x * TILE_SIZE, coll.pos_y * TILE_SIZE);
		i++;
	}
}

void	draw_enemies(t_game *game)
{
	int		i;
	t_enemy	enemy;

	i = 0;
	while (i < game->parse.total_enemies)
	{
		enemy = game->enemies[i];
		if (enemy.sprite)
			mlx_put_image_to_window(game->window.mlx, game->window.mlx_win,
				enemy.sprite, enemy.pos_x * TILE_SIZE, enemy.pos_y * TILE_SIZE);
		i++;
	}
}
