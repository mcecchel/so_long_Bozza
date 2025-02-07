#ifndef SO_LONG_H	
# define SO_LONG_H

# include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_map
{
	char	**map;
	int		rows;
	int		columns;
}				t_map;

typedef struct s_parse
{
	int		player;
	int		collectible;
	int		exit_game;
}				t_parse;

typedef struct s_game
{
	t_map	map;
	t_parse	parse;
	
}				t_game;	

// Map utils
void	free_matrix(char **matrix);
void	error_exit(const char *message, t_game *game);

// Valid path
void	find_player(t_game *game, int *pos_x, int *pos_y);
void	flood_fill(t_game *game, int x, int y);
int		check_reachability(t_game *game);
int		validate_path(t_game *game, int pos_x, int pos_y);

// Parse map
int		is_rectangular(t_game *game);
int		check_map_borders(t_game *game);
int		check_map_elements(t_game *game);
int		parse_map(t_game *game, const char *file_path);

#endif