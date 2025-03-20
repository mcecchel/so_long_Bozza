/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:18:42 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/20 18:34:56 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	srand(time(NULL));
	if (ac != 2)
		file_error_exit("Error\nInvalid number of arguments\n");
	validate_file(av[1]);
	game.map.map = read_map(av[1], &game);
	if (!game.map.map)
		file_error_exit("Error\nFailed to read map\n");
	game.map.map[game.player.py][game.player.px] = '0';
	game.window.mlx = mlx_init();
	if (!game.window.mlx)
		error_exit("Error\nFailed to initialize mlx\n", &game);
	game.window.mlx_win = mlx_new_window(game.window.mlx, game.map.columns
			* TILE_SIZE, game.map.rows * TILE_SIZE, "so_long");
	if (!game.window.mlx_win)
		error_exit("Error\nFailed to create window\n", &game);
	initialize_game(&game, game.window.mlx, game.window.mlx_win);
	mlx_hook(game.window.mlx_win, KeyPress, KeyPressMask, handle_keys, &game);
	mlx_hook(game.window.mlx_win, DestroyNotify, StructureNotifyMask,
		close_game, &game);
	mlx_loop(game.window.mlx);
	free_resources(&game);
	return (0);
}
