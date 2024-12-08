/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:34:27 by dde-giov          #+#    #+#             */
/*   Updated: 2023/05/14 16:52:55 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_ber(char *path)
{
	int		i;

	i = ft_strlen(path);
	while (i > ft_strlen(path) - 4 && path)
	{
		if (path[i] != ".ber"[i - ft_strlen(path) + 4])
		{
			ft_printf("Error\nInvalid map extension\n");
			return (-1);
		}
		i--;
	}
	return (1);
}

int	check_map(t_map map)
{
	int		y;

	y = 0;
	while (y < map.h)
	{
		if (y == 0 || y == check_maph(map) - 1)
		{
			if (check_map_frist_last_line(map.map[y], map) == -1)
				return (-1);
		}
		else
		{
			if (check_map_line(map.map[y], map, y) == -1)
				return (-1);
		}
		y++;
	}
	return (1);
}

char	**map_write(t_map map)
{
	int		fd;
	char	**map_matrix;
	char	*line;	
	int		i;

	i = 0;
	fd = open(map.path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map_matrix = malloc(sizeof(char *) * (check_maph(map) + 1));
	if (!map_matrix)
		return (NULL);
	while (i < check_maph(map))
	{
		line = get_next_line(fd);
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map_matrix[i] = line;
		i++;
	}
	return (map_matrix);
}

void	print_stats(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.w)
		put_image_spr(game, game->ground.spr, i++, game->map.h);
	print_str(game, "Moves:", game->moves, 1);
	if (game->carburante == 0)
		print_str2(game, "Out of fuel", -1, 1);
	else
		print_str2(game, "Fuel:", game->carburante, 1);
	if (game->map.w > 10)
	{
		print_str(game, "Retries:", game->retries, game->map.w - 3);
		print_str2(game, "Fuel rechargher:", game->collectible.n,
			game->map.w - 4);
	}
}

int	map_init(t_game *game)
{
	if (check_ber(game->map.path) == -1)
		return (-1);
	game->map.h = check_maph(game->map);
	game->map.map = map_write(game->map);
	game->map.w = check_mapw(game->map);
	if (map_counter(game) < 0)
		return (-1);
	if (check_map(game->map) == -1)
		return (-1);
	return (1);
}
