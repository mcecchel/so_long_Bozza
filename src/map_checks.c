/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:24:05 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/17 16:09:39 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_rectangular(t_game *game)
{
	int			i;
	
	i = 1;
	game->map.columns = ft_strlen(game->map.map[0]);
	while (i < game->map.rows)
	{
		if ((int)ft_strlen(game->map.map[i]) != game->map.columns)
		{
			error_exit("Error\nMap is not rectangular\n", game);
			return (0);// La mappa e' rettangolare
		}
		i++;
	}
	return (1);
}

// Se ritorna 0, la mappa non è valida perché non è chiusa correttamente
int	check_map_borders(t_game *game)
{
	int			i;
	
	i = 0;
	while (i < game->map.columns)// Controlla prima e ultima riga
	{
		if (game->map.map[0][i] != '1' || game->map.map[game->map.rows - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < game->map.rows)// Controlla i bordi laterali
	{
		if (game->map.map[i][0] != '1' || game->map.map[i][game->map.columns - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

// Verifico se c'e' esattamente un P, almeno un C e un solo E
int	check_map_elements(t_game *game)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.columns && game->map.map[i][j])
		{
			if (game->map.map[i][j] == 'P')
				game->parse.player++;
			else if (game->map.map[i][j] == 'C')
				game->parse.collectible++;
			else if (game->map.map[i][j] == 'E')
			game->parse.exit_game++;
			j++;
		}
		i++;
	}
	if (game->parse.player != 1 || game->parse.collectible < 1 || game->parse.exit_game != 1)
		return (0);// Mappa non valida
	return (1);
}

int	validate_map(t_game *game)
{
	if (!is_rectangular(game))
		return (0);
	if (!check_map_borders(game))
		return (0);
	if (!check_map_elements(game))
		return (0);
	return (1);
}

void	find_player(t_game *game, int *pos_x, int *pos_y)
{
	int			i;
	int			j;

	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (game->map.map[i][j] != '\0')
		{
			if (game->map.map[i][j] == 'P')
			{
				*pos_x = j;
				*pos_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	flood_fill(t_game *game, char **map, int x, int y)
{
	// Check se siamo fuori dalla mappa o su un muro, fermiamo la ricerca
	if (x < 0 || y < 0 || x >= game->map.columns || y >= game->map.rows
		|| map[y][x] == '1' || map[y][x] == 'V')
		return ;
	// Segna la posizione come visitata
	map[y][x] = 'V';
	// Espandi la ricerca in tutte le direzioni
	flood_fill(game, map, x + 1, y);
	flood_fill(game, map, x - 1, y);
	flood_fill(game, map, x, y + 1);
	flood_fill(game, map, x, y - 1);
}

// Controlla se ci sono ancora 'C' o 'E' non raggiunti
int	check_reachability(t_game *game, char **map)
{
	int			i;
	int			j;

	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'C' || map[i][j] == 'E')
				return (0);// Se ci sono ancora 'C' o 'E', la mappa non è valida
			j++;
		}
		i++;
	}
	return (1);// Tutti i 'C' e 'E' sono stati raggiunti
}

int	validate_path(t_game *game, int pos_x, int pos_y)
{
	int			i;
	char		**map_copy;
	int			reached;

	i = 0;
	find_player(game, &pos_x, &pos_y);
	// Crea una copia della mappa per non modificare l'originale
	map_copy = ft_calloc(game->map.rows + 1, sizeof(char *));
	while (i < game->map.rows)
	{
		map_copy[i] = ft_strdup(game->map.map[i]);
		if (!map_copy[i])
			error_exit("Error\nMemory allocation failed\n", game);
		i++;
	}
	// Espando ricorsivamente il percorso, marcando le posizioni già visitate
	flood_fill(game, map_copy, pos_x, pos_y);
	// Dopo il riempimento, controlla se E e tutti i C sono stati raggiunti
	reached = check_reachability(game, map_copy);
	free_matrix(map_copy);
	return (reached);
}
