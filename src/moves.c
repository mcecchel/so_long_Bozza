/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:40:49 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/12 19:50:42 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	show_moves(t_game *game)
{
	char	*moves;
	char	*moves_str;

	moves = ft_itoa(game->moves);
	if (!moves)
	{
		printf("Errore: ft_itoa ha restituito NULL\n");
		return ;
	}
	moves_str = ft_strjoin("Moves: ", moves);
	free(moves);
	if (!moves_str)
	{
		printf("Errore: ft_strjoin ha restituito NULL\n");
		return ;
	}
	mlx_put_image_to_window(game->window.mlx, game->window.mlx_win,
		game->sprites.moves_background, 1, 1);
	mlx_string_put(game->window.mlx, game->window.mlx_win,
		10, 12, 0x282828, moves_str);
	free(moves_str);
}

void	handle_collectibles(t_game *game, int new_x_pos, int new_y_pos)
{
	t_collectible	*collectible;

	collectible = is_collectible(game, new_x_pos, new_y_pos);
	if (collectible)
	{
		game->player.collected_items++;
		game->map.map[new_y_pos][new_x_pos] = '0';
		collectible->pos_x = -1;
		printf("Item collected! You have: %d of %d\n",
			game->player.collected_items, game->player.total_collectibles);
	}
}

void	handle_enemies(t_game *game, int new_x_pos, int new_y_pos)
{
	t_enemy	*enemy;

	enemy = is_enemy(game, new_x_pos, new_y_pos);
	if (enemy)
	{
		printf("Seems you have been caught by an enemy,"
			"AHAH.(read with Nelson voice)\a\n");
		free_resources(game);
		exit(0);
	}
}

void	move_player(t_game *game, int new_x_pos, int new_y_pos)
{
	if (new_y_pos >= 0 && new_y_pos < game->map.rows && new_x_pos >= 0
		&& new_x_pos < game->map.columns
		&& game->map.map[new_y_pos][new_x_pos] != '1')
	{
		game->player.px = new_x_pos;
		game->player.py = new_y_pos;
		move_all_enemies(game);
		handle_collectibles(game, new_x_pos, new_y_pos);
		handle_enemies(game, new_x_pos, new_y_pos);
		game->moves++;
		ft_printf("Moves: %d\n", game->moves);
		if (game->map.map[new_y_pos][new_x_pos] == 'E')
		{
			if (!all_collected(game))
				printf("Error\nNice try..."
					"You must collect all items to unlock the exit\n");
			else
			{
				printf("Congratulations! You have collected all items"
					"and reached the exit!\n");
				free_resources(game);
				exit(0);
			}
		}
	}
}
