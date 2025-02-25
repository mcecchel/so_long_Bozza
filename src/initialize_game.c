/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:29:06 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/25 18:35:26 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	random_coll_sprite(t_game *game)
{
	int width;
	int height;

	game->sprites.coll1 = mlx_xpm_file_to_image(game->window.mlx, "./textures/coll1.xpm", &width, &height);
	game->sprites.coll2 = mlx_xpm_file_to_image(game->window.mlx, "./textures/coll2.xpm", &width, &height);
	game->sprites.coll3 = mlx_xpm_file_to_image(game->window.mlx, "./textures/coll3.xpm", &width, &height);
	game->sprites.coll4 = mlx_xpm_file_to_image(game->window.mlx, "./textures/coll4.xpm", &width, &height);
	if (!game->sprites.coll1 || !game->sprites.coll2 || !game->sprites.coll3 || !game->sprites.coll4)
	{
		printf("Error\nFailed to load collectible sprite\n");
		free_resources(game);
		exit(1);
	}
}

void	draw_map(t_game *game, void *mlx, void *mlx_win)
{
	int		i;
	int		j;
	int		random_sprite;

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
			else if (game->map.map[i][j] == 'C')
			{
				random_sprite = rand() % 4;
				if (random_sprite == 0)
					mlx_put_image_to_window(mlx, mlx_win, game->sprites.coll1, j * TILE_SIZE, i * TILE_SIZE);
				else if (random_sprite == 1)
					mlx_put_image_to_window(mlx, mlx_win, game->sprites.coll2, j * TILE_SIZE, i * TILE_SIZE);
				else if (random_sprite == 2)
					mlx_put_image_to_window(mlx, mlx_win, game->sprites.coll3, j * TILE_SIZE, i * TILE_SIZE);
				else if (random_sprite == 3)
					mlx_put_image_to_window(mlx, mlx_win, game->sprites.coll4, j * TILE_SIZE, i * TILE_SIZE);
			}
			else if (game->map.map[i][j] == 'E')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.exit, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, game->sprites.player,
		game->player.px * TILE_SIZE, game->player.py * TILE_SIZE);
}

void	move_player(t_game *game, int new_x_pos, int new_y_pos)
{
	if (new_y_pos >= 0 && new_y_pos < game->map.rows && new_x_pos >= 0
		&& new_x_pos < game->map.columns && game->map.map[new_y_pos][new_x_pos] != '1')
	{
		game->player.px = new_x_pos;
		game->player.py = new_y_pos;
		if (game->map.map[new_y_pos][new_x_pos] == 'C')
		{
			game->player.collected_items++;
			game->map.map[new_y_pos][new_x_pos] = '0';
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
	random_coll_sprite(game);
	// game->sprites.collectible = mlx_xpm_file_to_image(mlx, "./textures/coll1.xpm", &width, &height);
	game->sprites.exit = mlx_xpm_file_to_image(mlx, "./textures/exit.xpm", &width, &height);
	if (!game->sprites.wall || !game->sprites.floor || !game->sprites.player || !game->sprites.coll1
		|| !game->sprites.coll2 || !game->sprites.coll3 || !game->sprites.coll4 || !game->sprites.exit)
		error_exit("Error\nFailed to load textures\n", game);
	draw_map(game, mlx, mlx_win);
}
