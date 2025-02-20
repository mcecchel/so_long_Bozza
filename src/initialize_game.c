/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:29:06 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/20 18:27:39 by mcecchel         ###   ########.fr       */
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
			else if (game->map.map[i][j] == 'P')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.player, j * TILE_SIZE, i * TILE_SIZE);
			else if (game->map.map[i][j] == 'C')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.collectible, j * TILE_SIZE, i * TILE_SIZE);
			else if (game->map.map[i][j] == 'E')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.exit, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
}

int	handle_keys(int keycode, t_game *game)
{
	int	new_x_pos;
	int	new_y_pos;
	
	new_x_pos = game->map.player_x;
	new_y_pos = game->map.player_y;
	if (keycode == 65307)// ESC
		exit(0);
	else if (keycode == 65362)// Freccia su
		new_y_pos -= 1;// Va di 1 su
	else if (keycode == 65364)// Freccia giù
		new_y_pos += 1;// Va di 1 giù
	else if (keycode == 65361)// Freccia sinistra
	new_x_pos -= 1;// Va di 1 a sinistra
	else if (keycode == 65363)// Freccia destra
	new_x_pos += 1;// Va di 1 a destra
	// Controlla se la nuova posizione è valida e dentro i limiti
	if (new_y_pos >= 0 && new_y_pos < game->map.rows && new_x_pos >= 0 && new_x_pos < game->map.columns && game->map.map[new_y_pos][new_x_pos] != '1')
	{
		game->map.player_x = new_x_pos;
		game->map.player_y = new_y_pos;
		mlx_clear_window(game->window.mlx, game->window.mlx_win);
		draw_map(game, game->window.mlx, game->window.mlx_win);
	}
	return (0);
}

void	initialize_game(t_game *game, void *mlx, void *mlx_win)
{
	int		width;
	int		height;

	// Carica gli sprite (immagini)
	game->sprites.wall = mlx_xpm_file_to_image(mlx, "./textures/wall.xpm", &width, &height);
	game->sprites.floor = mlx_xpm_file_to_image(mlx, "./textures/floor.xpm", &width, &height);
	game->sprites.player = mlx_xpm_file_to_image(mlx, "./textures/front_2.xpm", &width, &height);
	game->sprites.collectible = mlx_xpm_file_to_image(mlx, "./textures/collectible.xpm", &width, &height);
	game->sprites.exit = mlx_xpm_file_to_image(mlx, "./textures/exit.xpm", &width, &height);
	// Controlla che tutte le texture siano state caricate
	if (!game->sprites.wall || !game->sprites.floor || !game->sprites.player || !game->sprites.collectible || !game->sprites.exit)
		error_exit("Error\nFailed to load textures\n", game);
	draw_map(game, mlx, mlx_win);
}

void	destroy_sprites(t_game *game, void *mlx)
{
	mlx_destroy_image(mlx, game->sprites.wall);
	mlx_destroy_image(mlx, game->sprites.floor);
	mlx_destroy_image(mlx, game->sprites.player);
	mlx_destroy_image(mlx, game->sprites.collectible);
	mlx_destroy_image(mlx, game->sprites.exit);
}

int	main(int ac, char **av)
{
	t_game	game;
	void	*mlx;
	void	*mlx_win;
	
	ft_memset(&game, 0, sizeof(t_game));
	if (ac != 2)
		file_error_exit("Error\nInvalid number of arguments\n");
	validate_file(av[1]);
	game.map.map = read_map(av[1], &game);
	if (!game.map.map)
		file_error_exit("Error\nFailed to read map\n");
	mlx = mlx_init();
	if (!mlx)
		error_exit("Error\nFailed to initialize mlx\n", &game);
	mlx_win = mlx_new_window(mlx, game.map.columns * TILE_SIZE, game.map.rows * TILE_SIZE, "so_long");
	if (!mlx_win)
		error_exit("Error\nFailed to create window\n", &game);
	initialize_game(&game, mlx, mlx_win);
	mlx_key_hook(mlx_win, handle_keys, &game);
	mlx_mouse_hook(mlx_win, handle_keys, &game);
	
	mlx_loop(mlx);
	// Pulizia risorse
	destroy_sprites(&game, mlx);
	free_matrix(game.map.map);
	mlx_destroy_window(mlx, mlx_win);
	return (0);
}
