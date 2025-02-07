/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:55:26 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/07 12:57:40 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
//nella dichiarazione aggiungo una struttura che racchiude tutto per poi freeare tutto prima di exit 
void	error_exit(const char *message)
{
	write(2, message, ft_strlen(message));
	exit(1);
}

int	is_rectangular(char **map, int rows)
{
	int	i;
	int	columns;

	i = 1;
	columns = ft_strlen(map[0]);
	while (i < rows)
	{
		if (ft_strlen(map[i]) != columns)
			return (0);// La mappa e' rettangolare
		i++;
	}
	error_exit("Error\nMap is not rectangular\n");
	return (1);
}

// Se ritorna 0, la mappa non è valida perché non è chiusa correttamente
int	check_map_borders(char **map, int rows, int columns)
{
	int	i;
	
	i = 0;
	// Controlla prima e ultima riga
	while (i < columns)
	{
		if (map[0][i] != '1' || map[rows - 1][i] != '1')
			return (0);
		i++;
	}
	// Controlla i bordi laterali
	i = 0;
	while (i < rows)
	{
		if (map[i][0] != '1' || map[i][columns - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

// Verifico se c'e' esattamente un P, almeno un C e un solo E
int	check_map_elements(char **map, int rows, int columns)
{
	int	i;
	int	j;
	int	player;
	int	collectible;
	int	exit;

	i = 0;
	player = 0;
	collectible = 0;
	exit = 0;
	while (i < rows)
	{
		j = 0;
		while (j < columns && map[i][j])
		{
			if (map[i][j] == 'P')
				player++;
			else if (map[i][j] == 'C')
				collectible++;
			else if (map[i][j] == 'E')
				exit++;
			j++;
		}
		i++;
	}
	if (player != 1 || collectible < 1 || exit != 1)
		return (0);// Mappa non valida
	return (1);
}