/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:21:44 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/22 14:23:17 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Map utils
void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix != NULL && matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	error_exit(const char *message, t_game *game)
{
	size_t	return_value;

	return_value = write(2, message, ft_strlen(message));
	(void)return_value;
	free_matrix(game->map.map);
	exit(1);
}

// Free resources
void	destroy_sprites(t_game *game, void *mlx)
{
	mlx_destroy_image(mlx, game->sprites.wall);
	mlx_destroy_image(mlx, game->sprites.floor);
	mlx_destroy_image(mlx, game->sprites.player);
	mlx_destroy_image(mlx, game->sprites.collectible);
	mlx_destroy_image(mlx, game->sprites.exit);
}

void	free_resources(t_game *game)
{
	destroy_sprites(game, game->window.mlx);
	free_matrix(game->map.map);
	mlx_destroy_window(game->window.mlx, game->window.mlx_win);
	mlx_destroy_display(game->window.mlx);
	free(game->window.mlx);
}

