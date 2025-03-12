/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:29:06 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/12 20:00:33 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keys(int keycode, t_game *game)
{
	int	new_x_pos;
	int	new_y_pos;

	new_x_pos = game->player.px;
	new_y_pos = game->player.py;
	if (keycode == XK_Escape)
	{
		free_resources(game);
		exit(0);
	}
	else if (keycode == XK_Up)
	{
		new_y_pos -= 1;
		game->player.sprite = game->sprites.player.back;
	}
	else if (keycode == XK_Down)
	{
		new_y_pos += 1;
		game->player.sprite = game->sprites.player.front;
	}
	else if (keycode == XK_Left)
	{
		new_x_pos -= 1;
		game->player.sprite = game->sprites.player.left;
	}
	else if (keycode == XK_Right)
	{
		new_x_pos += 1;
		game->player.sprite = game->sprites.player.right;
	}
	if (keycode == XK_Up || keycode == XK_Down || keycode == XK_Left
		|| keycode == XK_Right)
	{
		move_player(game, new_x_pos, new_y_pos);
		draw_map(game, game->window.mlx, game->window.mlx_win);
	}
	return (0);
}

void	draw_map(t_game *game, void *mlx, void *mlx_win)
{
	int		i;
	int		j;

	i = 0;
	while (game->map.map[i] != NULL)
	{
		j = 0;
		while (game->map.map[i][j] != '\0')
		{
			if (game->map.map[i][j] == '1')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.wall,
					j * TILE_SIZE, i * TILE_SIZE);
			else if (game->map.map[i][j] == '0')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.floor,
					j * TILE_SIZE, i * TILE_SIZE);
			else if (game->map.map[i][j] == 'E')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.exit,
					j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
	draw_collectibles(game);
	mlx_put_image_to_window(mlx, mlx_win, game->player.sprite,
		game->player.px * TILE_SIZE, game->player.py * TILE_SIZE);
	draw_enemies(game);
	show_moves(game);
}

void	initialize_game(t_game *game, void *mlx, void *mlx_win)
{
	get_other_sprite(game);
	get_player_sprite(game);
	game->player.sprite = game->sprites.player.front;
	get_coll_sprite(game);
	get_enemy_sprite(game);
	initialize_collectibles(game);
	initialize_enemies(game);
	draw_map(game, mlx, mlx_win);
}
