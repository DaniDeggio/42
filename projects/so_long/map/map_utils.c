/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:56:26 by dde-giov          #+#    #+#             */
/*   Updated: 2023/05/17 15:50:16 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	map_initelem(t_game *game)
{
	game->player.n = 0;
	game->exit.n = 0;
	game->collectible.n = 0;
	game->ground.n = 0;
	game->wall.n = 0;
	game->laserx = 0;
	game->moves = 0;
}

void	map_assignetion(t_game *game, char c, int x, int y)
{
	if (c == 'P')
	{
		game->player.n++;
		game->player.x = x;
		game->player.y = y;
	}
	if (c == 'E')
	{
		game->exit.n++;
		game->exit.x = x;
		game->exit.y = y;
	}
	if (c == 'C')
		game->collectible.n++;
	if (c == '0')
		game->ground.n++;
	if (c == '1')
		game->wall.n++;
}

int	check_element_n(t_game *game)
{
	if (game->player.n > 1)
	{
		ft_printf("Error\nToo many players on the map\n");
		return (-1);
	}
	if (game->player.n == 0)
	{
		ft_printf("Error\nNo player on the map\n");
		return (-1);
	}
	if (game->exit.n == 0)
	{
		ft_printf("Error\nNo exit on the map\n");
		return (-1);
	}
	if (game->collectible.n == 0)
	{
		ft_printf("Error\nNo collectible on the map\n");
		return (-1);
	}
	return (1);
}

int	map_counter(t_game *game)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	map_initelem(game);
	while (y < game->map.h)
	{
		while (game->map.map[y][i])
		{
			map_assignetion(game, game->map.map[y][i], i, y);
			i++;
		}
		i = 0;
		y++;
	}
	game->col_ini = game->collectible.n;
	if (check_element_n(game) < 0)
		return (-1);
	return (1);
}

void	print_ground(t_game *game, int x)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < game->map.w && i < x)
	{
		while (j < game->map.h + 1)
			put_image_spr(game, game->ground.spr, i, j++);
		j = 0;
		i++;
	}
}
