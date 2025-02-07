/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:12:33 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/07 18:46:34 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_rectangular(t_game *game)
{
	int			i;
	const char	**map = game->map.map;
	const int	rows = game->map.rows;
	
	i = 1;
	game->map.columns = ft_strlen(map[0]);
	while (i < rows)
	{
		if (ft_strlen(map[i]) != game->map.columns)
			return (0);// La mappa e' rettangolare
		i++;
	}
	error_exit("Error\nMap is not rectangular\n", game);
	return (1);
}

/* int main(void)
{
    t_game game;
    const char *map_data[] = {
        "1111",
        "1001",
        "1001",
        "1111",
        NULL
    };

    game.map.map = map_data;
    game.map.rows = 4;

    if (is_rectangular(&game))
        printf("The map is rectangular.\n");
    else
        printf("The map is not rectangular.\n");

    return 0;
} */

// Se ritorna 0, la mappa non è valida perché non è chiusa correttamente
int	check_map_borders(t_game *game)
{
	int			i;
	const char	**map = game->map.map;
	const int	rows = game->map.rows;
	const int	columns = game->map.columns;
	
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
	if (game->parse.player != 1 || game->parse.collectible < 1 || exit != 1)
		return (0);// Mappa non valida
	return (1);
}