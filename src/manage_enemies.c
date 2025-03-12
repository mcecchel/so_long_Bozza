/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:52:43 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/12 19:42:00 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_enemies(t_game *game)
{
	int	i;
	int	j;
	int	en_index;

	game->enemies = ft_calloc(game->player.total_enemies, sizeof(t_enemy));
	if (!game->enemies)
		error_exit("Error\nMemory allocation failed\n", game);
	i = -1;
	en_index = 0;
	while (game->map.map[++i] != NULL)
	{
		j = 0;
		while (game->map.map[i][j] != '\0')
		{
			if (game->map.map[i][j] == 'N')
			{
				game->enemies[en_index].pos_x = j;
				game->enemies[en_index].pos_y = i;
				game->enemies[en_index].sprite = get_random_enemy_sprite(game);
				game->map.map[i][j] = '0';
				en_index++;
			}
			j++;
		}
	}
}

void	draw_enemies(t_game *game)
{
	int		i;
	t_enemy	enemy;

	i = 0;
	while (i < game->player.total_enemies)
	{
		enemy = game->enemies[i];
		if (enemy.sprite)
			mlx_put_image_to_window(game->window.mlx, game->window.mlx_win,
				enemy.sprite, enemy.pos_x * TILE_SIZE, enemy.pos_y * TILE_SIZE);
		i++;
	}
}

t_enemy	*is_enemy(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->player.total_enemies)
	{
		if (game->enemies[i].pos_x == x && game->enemies[i].pos_y == y)
			return (&game->enemies[i]);
		i++;
	}
	return (NULL);
}

void	move_enemy(t_game *game, t_enemy *enemy, int new_x_pos, int new_y_pos)
{
	if (new_y_pos >= 0 && new_y_pos < game->map.rows && new_x_pos >= 0
		&& new_x_pos < game->map.columns
		&& game->map.map[new_y_pos][new_x_pos] != '1'
		&& !is_enemy(game, new_x_pos, new_y_pos))
	{
		enemy->pos_x = new_x_pos;
		enemy->pos_y = new_y_pos;
	}
}

void	move_all_enemies(t_game *game)
{
	int	new_x_pos;
	int	new_y_pos;
	int	i;

	i = 0;
	while (i < game->player.total_enemies)
	{
		new_x_pos = game->enemies[i].pos_x;
		new_y_pos = game->enemies[i].pos_y;
		if (rand() % 2 == 0)
		{
			if (rand() % 2 == 0)
			{
				game->enemies[i].sprite = game->sprites.enemy.sx;
				new_x_pos--;
			}
			else
			{
				game->enemies[i].sprite = game->sprites.enemy.dx;
				new_x_pos++;
			}
		}
		else
		{
			if (rand() % 2 == 0)
				new_y_pos--;
			else
				new_y_pos++;
		}
		move_enemy(game, &game->enemies[i], new_x_pos, new_y_pos);
		i++;
	}
}
