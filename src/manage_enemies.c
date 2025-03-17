/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:52:43 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/17 14:44:00 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_enemies(t_game *game)
{
	int	i;
	int	j;
	int	en_index;

	game->enemies = ft_calloc(game->parse.total_enemies, sizeof(t_enemy));
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

t_enemy	*is_enemy(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->parse.total_enemies)
	{
		if (game->enemies[i].pos_x == x && game->enemies[i].pos_y == y)
			return (&game->enemies[i]);
		i++;
	}
	return (NULL);
}

void	determine_new_position(t_game *game, t_enemy *enemy,
	int *new_x_pos, int *new_y_pos)
{
	*new_x_pos = enemy->pos_x;
	*new_y_pos = enemy->pos_y;
	if (rand() % 2 == 0)
	{
		if (rand() % 2 == 0)
		{
			enemy->sprite = game->sprites.enemy.sx;
			(*new_x_pos)--;
		}
		else
		{
			enemy->sprite = game->sprites.enemy.dx;
			(*new_x_pos)++;
		}
	}
	else
	{
		if (rand() % 2 == 0)
			(*new_y_pos)--;
		else
			(*new_y_pos)++;
	}
}

void	move_enemy(t_game *game, t_enemy *enemy)
{
	int	new_x_pos;
	int	new_y_pos;

	determine_new_position(game, enemy, &new_x_pos, &new_y_pos);
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
	int	i;

	i = 0;
	while (i < game->parse.total_enemies)
	{
		move_enemy(game, &game->enemies[i]);
		i++;
	}
}
