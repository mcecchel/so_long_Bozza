/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:29:06 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/27 15:24:01 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.wall, j * TILE_SIZE, i * TILE_SIZE);
			else if (game->map.map[i][j] == '0')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.floor, j * TILE_SIZE, i * TILE_SIZE);
			else if (game->map.map[i][j] == 'E')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.exit, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
	draw_collectibles(game);
	mlx_put_image_to_window(mlx, mlx_win, game->sprites.player,
		game->player.px * TILE_SIZE, game->player.py * TILE_SIZE);
}

void	move_player(t_game *game, int new_x_pos, int new_y_pos)
{
	t_collectible	*collectible;
	
	if (new_y_pos >= 0 && new_y_pos < game->map.rows && new_x_pos >= 0
		&& new_x_pos < game->map.columns && game->map.map[new_y_pos][new_x_pos] != '1')
	{
		game->player.px = new_x_pos;
		game->player.py = new_y_pos;
		collectible = is_collectible(game, new_x_pos, new_y_pos);
		if (collectible)
		{
			game->player.collected_items++;
			game->map.map[new_y_pos][new_x_pos] = '0';
			collectible->pos_x = -1; // Cosi' so che e' stato collezionato
			printf("Item collected! You have: %d of %d\n", game->player.collected_items, game->player.total_collectibles);
		}
		draw_map(game, game->window.mlx, game->window.mlx_win);
		if (game->map.map[new_y_pos][new_x_pos] == 'E')
		{
			if (!all_collected(game))
				printf("Error\nNice try... You must collect all items to unlock the exit\n");
			else
			{
				printf("Congratulations! You have collected all items and reached the exit!\n");
				free_resources(game);
				exit(0);
			}
		}
	}
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
	else if (keycode == XK_Up)
		new_y_pos -= 1;
	else if (keycode == XK_Down)
		new_y_pos += 1;
	else if (keycode == XK_Left)
		new_x_pos -= 1;
	else if (keycode == XK_Right)
		new_x_pos += 1;
	move_player(game, new_x_pos, new_y_pos);
	return (0);
}

bool	all_collected(t_game *game)
{
	if (game->player.collected_items == game->player.total_collectibles)
		return (true);
	return (false);
}

void	initialize_game(t_game *game, void *mlx, void *mlx_win)
{
	int		width;
	int		height;

	game->sprites.wall = mlx_xpm_file_to_image(mlx, "./textures/wall.xpm", &width, &height);
	game->sprites.floor = mlx_xpm_file_to_image(mlx, "./textures/floor.xpm", &width, &height);
	game->sprites.player = mlx_xpm_file_to_image(mlx, "./textures/front2.xpm", &width, &height);
	game->sprites.exit = mlx_xpm_file_to_image(mlx, "./textures/exit.xpm", &width, &height);
	init_coll_sprite(game);
	initialize_collectibles(game);
	if (!game->sprites.wall || !game->sprites.floor || !game->sprites.player || !game->sprites.collectible.coll1
		|| !game->sprites.collectible.coll2 || !game->sprites.collectible.coll3 || !game->sprites.collectible.coll4 || !game->sprites.exit)
		error_exit("Error\nFailed to load textures\n", game);
	draw_map(game, mlx, mlx_win);
}
