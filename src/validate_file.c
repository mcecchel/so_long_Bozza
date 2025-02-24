/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:20:36 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/24 19:46:50 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	has_ber_extension(const char *filename)
{
	const char	*extension;

	extension = ft_strrchr(filename, '.');
	if (ft_strncmp(extension, ".ber", 4) != 0)
		return (0);
	return (1);
}

int	file_exists(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	is_folder(const char *filename)
{
	int		fd;

	fd = open(filename, O_DIRECTORY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	is_readable(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

void	validate_file(const char *filename)
{
	if (!has_ber_extension(filename))
		file_error_exit("Error\nInvalid file extension\n");
	else if (!file_exists(filename))
		file_error_exit("Error\nFile does not exist\n");
	else if (is_folder(filename))
		file_error_exit("Error\nFile is a directory\n");
	else if (!is_readable(filename))
		file_error_exit("Error\nFile is not readable\n");
	else
		return ;
}
