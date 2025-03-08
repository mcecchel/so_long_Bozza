#ifndef SO_LONG_H	
# define SO_LONG_H

#include "libft.h"
#include <mlx.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <mlx_int.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
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
}				t_map;

typedef struct s_player
{
	int		px;
	int		py;
	int		collected_items;
	int		total_collectibles;
	int		total_enemies;
}				t_player;

typedef struct s_parse
{
	int		player;
	int		collectible;
	int		exit_game;
}				t_parse;

typedef struct s_enemy
{
	int		pos_x;
	int		pos_y;
	void	*sprite;
}				t_enemy;

typedef struct s_sprite_enemy
{
	void *dx;
	void *sx;
}				t_sprite_enemy;

typedef struct s_collectible
{
	int		pos_x;
	int		pos_y;
	void	*sprite;
}				t_collectible;

typedef struct s_sprite_coll
{
	void *coll1;
	void *coll2;
	void *coll3;
	void *coll4;
}				t_sprite_coll;

#define TILE_SIZE 32// Costante per la dimensione degli sprites
typedef struct s_sprites
{
    void			*player;
    void			*wall;
	void			*floor;
	t_sprite_coll	collectible;
	t_sprite_enemy	enemy;
	void			*moves_background;
	void			*exit;
}				t_sprites;

typedef struct s_window
{
	void	*mlx;
	void	*mlx_win;
	int		img_width;
	int		img_height;
}				t_window;

typedef struct s_game
{
	t_map			map;
	t_parse			parse;
	t_collectible	*collectibles;
	t_sprites		sprites;
	t_window		window;
	t_player		player;
	t_enemy			*enemies;
	int				moves;
	
}				t_game;	

// Utils
void	show_moves(t_game *game);
void	print_matrix(char **matrix);
void	free_matrix(char **matrix);
void	destroy_sprites(t_game *game, void *mlx);
void	free_resources(t_game *game);
int		close_game(t_game *game);

// Manage errors
void	error_exit(const char *message, t_game *game);
void	file_error_exit(const char *message);

// Check map validity
int		is_rectangular(t_game *game);
int		check_map_borders(t_game *game);
void	count_map_elements(t_game *game);
int		check_map_elements(t_game *game);
int		validate_map(t_game *game);

// Check path validity
void	find_player(t_game *game);
void	flood_fill(t_game *game, char **map, int x, int y);
int		check_reachability(t_game *game, char **map);
int		validate_path(t_game *game);

// Validate file
int		has_ber_extension(const char *filename);
int		file_exists(const char *filename);
int		is_folder(const char *filename);
int		is_readable(const char *filename);
void	validate_file(const char *filename);

// Get sprites
void	get_coll_sprite(t_game *game);
void	get_enemy_sprite(t_game *game);
void	get_sprite(t_game *game);

// Manage collectibles
void			*get_random_coll_sprite(t_game *game);
void			initialize_collectibles(t_game *game);
void			draw_collectibles(t_game *game);
t_collectible	*is_collectible(t_game *game, int x, int y);
bool			all_collected(t_game *game);

// Manage enemies
void			*get_random_enemy_sprite(t_game *game);
void			initialize_enemies(t_game *game);
void			draw_enemies(t_game *game);
t_enemy			*is_enemy(t_game *game, int x, int y);

// Load map
int				count_lines(const char *filename);
char			**load_map(const char *filename, t_game *game);
char			**read_map(const char *filename, t_game *game);

// Game initialization
void			draw_map(t_game *game, void *mlx, void *mlx_win);
void			move_player(t_game *game, int new_x_pos, int new_y_pos);
int				handle_keys(int keycode, t_game *game);
void			initialize_game(t_game *game, void *mlx, void *mlx_win);

int	main(int ac, char **av);

#endif
