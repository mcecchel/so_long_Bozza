/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:37:38 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/10 15:33:07 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	write(2, message, ft_strlen(message));
	free_matrix(game->map.map);
	exit(1);
}