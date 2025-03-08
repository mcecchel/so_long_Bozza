/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:21:44 by mcecchel          #+#    #+#             */
/*   Updated: 2025/03/08 16:54:36 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	show_moves(t_game *game)
{
	char	*moves;
	char	*moves_str;

	moves = ft_itoa(game->moves);
	if (!moves)
	{
		printf("Errore: ft_itoa ha restituito NULL\n");
		return ;
	}
	moves_str = ft_strjoin("Moves: ", moves);
	free(moves);
	if (!moves_str)
	{
		printf("Errore: ft_strjoin ha restituito NULL\n");
		return ;
	}
/* 	while (i < 75)
	{
		j = 0;
		while (j < 15)
		{
			mlx_pixel_put(game->window.mlx, game->window.mlx_win, i, j, 0xFFFFFF);
			j++;
		}
		i++;
	} */
	mlx_put_image_to_window(game->window.mlx, game->window.mlx_win, game->sprites.moves_background, 1, 1);
	mlx_string_put(game->window.mlx, game->window.mlx_win, 10, 12, 0x282828, moves_str);
	free(moves_str);
}

// Map utils
void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix != NULL && matrix[i] != NULL)
	{
		ft_printf("%s\n", matrix[i]);
		i++;
	}
}

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

// Free & exit game
void	destroy_sprites(t_game *game, void *mlx)
{
	if (game->sprites.wall)
		mlx_destroy_image(mlx, game->sprites.wall);
	if (game->sprites.floor)
		mlx_destroy_image(mlx, game->sprites.floor);
	if (game->sprites.player)
		mlx_destroy_image(mlx, game->sprites.player);
	if (game->sprites.collectible.coll1)
		mlx_destroy_image(mlx, game->sprites.collectible.coll1);
	if (game->sprites.collectible.coll2)
		mlx_destroy_image(mlx, game->sprites.collectible.coll2);
	if (game->sprites.collectible.coll3)
		mlx_destroy_image(mlx, game->sprites.collectible.coll3);
	if (game->sprites.collectible.coll4)
		mlx_destroy_image(mlx, game->sprites.collectible.coll4);
	if (game->sprites.enemy.dx)
		mlx_destroy_image(mlx, game->sprites.enemy.dx);
	if (game->sprites.enemy.sx)
		mlx_destroy_image(mlx, game->sprites.enemy.sx);
	if (game->sprites.exit)
		mlx_destroy_image(mlx, game->sprites.exit);
	if (game->sprites.moves_background)
		mlx_destroy_image(mlx, game->sprites.moves_background);
}

void	free_resources(t_game *game)
{
	destroy_sprites(game, game->window.mlx);
	free_matrix(game->map.map);
	if (game->window.mlx_win)
		mlx_destroy_window(game->window.mlx, game->window.mlx_win);
	mlx_destroy_display(game->window.mlx);
	free(game->collectibles);
	free(game->enemies);
	free(game->window.mlx);
}

int	close_game(t_game *game)
{
	free_resources(game);
	exit(0);
	return (0);
}
