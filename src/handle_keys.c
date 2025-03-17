/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:29:06 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/17 15:42:29 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_movement(int keycode, t_game *game,
	int *new_x_pos, int *new_y_pos)
{
	if (keycode == XK_Up)
	{
		*new_y_pos -= 1;
		game->player.sprite = game->sprites.player.back;
	}
	else if (keycode == XK_Down)
	{
		*new_y_pos += 1;
		game->player.sprite = game->sprites.player.front;
	}
	else if (keycode == XK_Left)
	{
		*new_x_pos -= 1;
		game->player.sprite = game->sprites.player.left;
	}
	else if (keycode == XK_Right)
	{
		*new_x_pos += 1;
		game->player.sprite = game->sprites.player.right;
	}
}

void	update_player_position(t_game *game, int new_x_pos, int new_y_pos)
{
	move_player(game, new_x_pos, new_y_pos);
	draw_map(game, game->window.mlx, game->window.mlx_win);
}

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
	handle_movement(keycode, game, &new_x_pos, &new_y_pos);
	if (keycode == XK_Up || keycode == XK_Down
		|| keycode == XK_Left || keycode == XK_Right)
		update_player_position(game, new_x_pos, new_y_pos);
	return (0);
}
