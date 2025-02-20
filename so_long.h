#ifndef SO_LONG_H	
# define SO_LONG_H

#include "libft.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define WALL '1'
#define EMPTY '0'
#define PLAYER 'P'
#define COLLECTIBLE 'C'
#define EXIT 'E'

typedef struct s_map
{
	char	**map;
	int		rows;
	int		columns; 
    int		player_x;
    int		player_y;
}				t_map;

typedef struct s_parse
{
	int		player;
	int		collectible;
	int		exit_game;
}				t_parse;

#define TILE_SIZE 32 // Costante per la dimensione degli sprites
typedef struct s_sprites
{
    void *player;
    void *wall;
	void *floor;
    void *collectible;
    void *exit;
}				t_sprites;

typedef struct s_window
{
	void	*mlx;
	void	*mlx_win;
}				t_window;

typedef struct s_game
{
	t_map		map;
	t_parse		parse;
	t_sprites	sprites;
	t_window	window;
	
}				t_game;	

// Map utils
void	free_matrix(char **matrix);
void	error_exit(const char *message, t_game *game);

// Check map validity
int		is_rectangular(t_game *game);
int		check_map_borders(t_game *game);
int		check_map_elements(t_game *game);
int		validate_map(t_game *game);
// Check path validity
void	find_player(t_game *game, int *pos_x, int *pos_y);
void	flood_fill(t_game *game, char **map, int x, int y);
int		check_reachability(t_game *game, char **map);
int		validate_path(t_game *game, int pos_x, int pos_y);

// Validate file
void	file_error_exit(const char *message);
int		has_ber_extension(const char *filename);
int		file_exists(const char *filename);
int		is_folder(const char *filename);
int		is_readable(const char *filename);
void	validate_file(const char *filename);

// Load map
int		count_lines(const char *filename);
char	**load_map(const char *filename, t_game *game);
char	**read_map(const char *filename, t_game *game);

// int	main(int ac, char **av)
#endif
