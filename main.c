/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:18:42 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/17 11:34:16 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* int	main(int ac, char **av)
{
	t_game	game;

	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	if (!mlx)
		error_exit("Error\nFailed to initialize mlx\n", &game);
	mlx_win = mlx_new_window(mlx, 1920, 1080, "so_long");
	if (!mlx_win)
		error_exit("Error\nFailed to create window\n", &game);
	mlx_loop(mlx);
	
	ft_memset(&game, 0, sizeof(t_game));
	if (ac != 2)
		file_error_exit("Error\nInvalid number of arguments\n");
	validate_file(av[1]);
	game.map.map = read_map(av[1], &game);
	free_matrix(game.map.map);
	return (0);
} */