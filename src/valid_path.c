/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:09:34 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/07 18:47:27 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* -----------------------------------------------------------------------------
Queste funzioni servono per verificare la validit' della mappa tramite il
controllo sulla validita' del percorso.
1) Trova la posizione del giocatore (P)
2) Crea una copia della mappa per non modificare l'originale
3) Espandi ricorsivamente il percorso, marcando le posizioni già visitate
4) Dopo il riempimento, controlla se E e tutti i C sono stati raggiunti
----------------------------------------------------------------------------- */
#include "so_long.h"

void	find_player(t_game *game, int *pos_x, int *pos_y)
{
	int			i;
	int			j;
	const char	**map = game->map.map;
	const int	rows = game->map.rows;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'P')
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

void	flood_fill(t_game *game, int x, int y)
{
	// Check se siamo fuori dalla mappa o su un muro, fermiamo la ricerca
	if (x < 0 || y < 0 || x >= game->map.columns || y >= game->map.rows
		|| game->map.map[y][x] == '1' || game->map.map[y][x] == 'V')
		return ;
	// Segna la posizione come visitata
	game->map.map[y][x] = 'V';
	// Espandi la ricerca in tutte le direzioni
	flood_fill(game->map.map, x + 1, y);
	flood_fill(game->map.map, x - 1, y);
	flood_fill(game->map.map, x, y + 1);
	flood_fill(game->map.map, x, y - 1);
}

// Controlla se ci sono ancora 'C' o 'E' non raggiunti
int	check_reachability(t_game *game)
{
	int			i;
	int			j;
	const char	**map = game->map.map;
	const int	rows = game->map.rows;

	i = 0;
	while (i < rows)
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
}

int	validate_path(t_game *game, int pos_x, int pos_y)
{
	int			i;
	char		**map_copy;
	int			reached;

	i = 0;
	// Trova la posizione del giocatore
	find_player(game, &pos_x, &pos_y);
	// Crea una copia della mappa per non modificare l'originale
	map_copy = ft_calloc(game->map.rows, sizeof(char *));
	while (i < game->map.rows)
	{
		map_copy[i] = ft_strdup(game->map.map[i]);
		if (!map_copy[i])
			error_exit("Error\nMemory allocation failed\n", game);
		i++;
	}
	// Espando ricorsivamente il percorso, marcando le posizioni già visitate
	flood_fill(game, pos_x, pos_y);
	// Dopo il riempimento, controlla se E e tutti i C sono stati raggiunti
	reached = check_reachability(game);
	free_matrix(map_copy);
	return (reached);
}
