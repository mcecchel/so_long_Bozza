/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:18:42 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/10 18:17:06 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (ac != 2)
		file_error_exit("Error\nInvalid number of arguments\n");
	validate_file(av[1]);
	game.map.map = read_map(av[1], &game);
	free_matrix(game.map.map);
	return (0);
}