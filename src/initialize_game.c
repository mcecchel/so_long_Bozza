/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:29:06 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/24 21:04:18 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*void	randomize_coll_sprite(t_game *game)
{
	int width;
	int height;
	int random_sprite = rand() % 4; // Assuming you have 3 different collectible sprites

	if (random_sprite == 0)
		game->sprites.collectible = mlx_xpm_file_to_image(game->window.mlx, "./textures/coll1.xpm", &width, &height);
	else if (random_sprite == 1)
		game->sprites.collectible = mlx_xpm_file_to_image(game->window.mlx, "./textures/coll2.xpm", &width, &height);
	else if (random_sprite == 2)
		(game->sprites.collectible = mlx_xpm_file_to_image(game->window.mlx, "./textures/coll3.xpm", &width, &height));
	else if (random_sprite == 3)
		(game->sprites.collectible = mlx_xpm_file_to_image(game->window.mlx, "./textures/coll4.xpm", &width, &height));
	if (!game->sprites.collectible)
	{
		printf("Error\nFailed to load collectible sprite\n");
		free_resources(game);
		exit(1);
	}
}
*/
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
			else if (game->map.map[i][j] == 'C')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.collectible, j * TILE_SIZE, i * TILE_SIZE);
			else if (game->map.map[i][j] == 'E')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.exit, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, game->sprites.player,
		game->player.px * TILE_SIZE, game->player.py * TILE_SIZE);
}
/* int	handle_keys(int keycode, t_game *game)
{
	int	new_x_pos;
	int	new_y_pos;
	
	new_x_pos = game->player.px;
	new_y_pos = game->player.py;
	if (keycode == XK_Escape)// ESC
	{
		free_resources(game);
		exit(0);
	}
	else if (keycode == XK_Up)// Freccia su
		new_y_pos -= 1;// Va di 1 su
	else if (keycode == XK_Down)// Freccia giù
		new_y_pos += 1;// Va di 1 giù
	else if (keycode == XK_Left)// Freccia sinist`ra
		new_x_pos -= 1;// Va di 1 a sinistra
	else if (keycode == XK_Right)// Freccia destra
		new_x_pos += 1;// Va di 1 a destra
	// Controlla se la nuova posizione è valida e dentro i limiti
	if (new_y_pos >= 0 && new_y_pos < game->map.rows && new_x_pos >= 0 && new_x_pos < game->map.columns && game->map.map[new_y_pos][new_x_pos] != '1')
	{
		game->player.px = new_x_pos;
		game->player.py = new_y_pos;
		// Controlla se il giocatore ha raccolto un oggetto
		if (game->map.map[new_y_pos][new_x_pos] == 'C')
		{
			game->player.collected_items++;
			game->map.map[new_y_pos][new_x_pos] = '0';
			printf("Item collected! You have: %d of %d\n", game->player.collected_items, game->player.total_collectibles);
		}
		// Controlla se il giocatore ha raggiunto l'uscita
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
	return (0);
*/

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

void	handle_keys(int keycode, t_game *game)
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
	game->sprites.collectible = mlx_xpm_file_to_image(mlx, "./textures/coll1.xpm", &width, &height);
	game->sprites.exit = mlx_xpm_file_to_image(mlx, "./textures/exit.xpm", &width, &height);
	if (!game->sprites.wall || !game->sprites.floor || !game->sprites.player
		|| !game->sprites.collectible || !game->sprites.exit)
		error_exit("Error\nFailed to load textures\n", game);
	draw_map(game, mlx, mlx_win);
}
