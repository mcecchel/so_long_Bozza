#include "so_long.h"

void	draw_map(t_game *game, void *mlx, void *mlx_win)
{
	int		i;
	int		j;

	i = 0;
	while (game->map.map[i] != NULL)
	{
		j = 0;
		while (game->map.map[i][j] != '\0')
		{
			if (game->map.map[i][j] == '1')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.wall, j * TILE_SIZE, i * TILE_SIZE);
			else if (game->map.map[i][j] == '0')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.floor, j * TILE_SIZE, i * TILE_SIZE);
			else if (game->map.map[i][j] == 'P')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.player, j * TILE_SIZE, i * TILE_SIZE);
			else if (game->map.map[i][j] == 'C')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.collectible, j * TILE_SIZE, i * TILE_SIZE);
			else if (game->map.map[i][j] == 'E')
				mlx_put_image_to_window(mlx, mlx_win, game->sprites.exit, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
}

void	initialize_game(t_game *game, void *mlx, void *mlx_win)
{
	int		width;
	int		height;

	// Carica gli sprite (immagini)
	game->sprites.player = mlx_xpm_file_to_image(mlx, "./textures/floor.xpm", &width, &height);
	game->sprites.wall = mlx_xpm_file_to_image(mlx, "./textures/wall.xpm", &width, &height);
	game->sprites.floor = mlx_xpm_file_to_image(mlx, "./textures/floor.xpm", &width, &height);
	game->sprites.collectible = mlx_xpm_file_to_image(mlx, "./textures/floor.xpm", &width, &height);
	game->sprites.exit = mlx_xpm_file_to_image(mlx, "./textures/floor.xpm", &width, &height);

	// Disegna la mappa
	draw_map(game, mlx, mlx_win);
}

int	main(int ac, char **av)
{
	t_game	game;
	
	void	*mlx;
	void	*mlx_win;
	
	ft_memset(&game, 0, sizeof(t_game));
	if (ac != 2)
	file_error_exit("Error\nInvalid number of arguments\n");
	validate_file(av[1]);
	game.map.map = read_map(av[1], &game);
	mlx = mlx_init();
	if (!mlx)
		error_exit("Error\nFailed to initialize mlx\n", &game);
	mlx_win = mlx_new_window(mlx, game.map.columns * TILE_SIZE, game.map.rows * TILE_SIZE, "so_long");
	// printf("Map size: rows = %d, columns = %d\n", game.map.rows, game.map.columns);
	if (!mlx_win)
		error_exit("Error\nFailed to create window\n", &game);
	initialize_game(&game, mlx, mlx_win);
	mlx_loop(mlx);
	
	// Pulizia risorse
	mlx_destroy_image(mlx, game.sprites.player);
	mlx_destroy_image(mlx, game.sprites.wall);
	mlx_destroy_image(mlx, game.sprites.collectible);
	free_matrix(game.map.map);
	return (0);
}