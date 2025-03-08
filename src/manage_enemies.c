/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:52:43 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/08 16:04:23 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

void	*get_random_enemy_sprite(t_game *game)
{
	int	random_sprite;

	random_sprite = rand() % 2;
	if (random_sprite == 0)
		return (game->sprites.enemy.dx);
	else
		return (game->sprites.enemy.sx);
}

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
			mlx_put_image_to_window(game->window.mlx, game->window.mlx_win, enemy.sprite, enemy.pos_x * TILE_SIZE, enemy.pos_y * TILE_SIZE);
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
