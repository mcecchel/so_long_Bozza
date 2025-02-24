/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:24:14 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/24 19:40:30 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(const char *message, t_game *game)
{
	size_t	return_value;

	return_value = write(2, message, ft_strlen(message));
	(void)return_value;
	free_matrix(game->map.map);
	exit(1);
}

void	file_error_exit(const char *message)
{
	size_t	return_value;

	return_value = write(2, message, ft_strlen(message));
	(void)return_value;
	exit(1);
}
