/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:26:26 by dde-giov          #+#    #+#             */
/*   Updated: 2023/05/14 16:56:37 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	move(t_game *game, int x, int y, char c)
{
	game->moves++;
	game->carburante--;
	put_image_spr(game, game->ground.spr, x, y);
	if (c == 'w')
		put_image_spr(game, game->ground.spr, x, y - 1);
	else if (c == 'a')
		put_image_spr(game, game->ground.spr, x - 1, y);
	else if (c == 's')
		put_image_spr(game, game->ground.spr, x, y + 1);
	else if (c == 'd')
		put_image_spr(game, game->ground.spr, x + 1, y);
	if (c == 'w')
		put_image_spr(game, game->player.spr, x, y - 1);
	else if (c == 'a')
		put_image_spr(game, game->player.spr, x - 1, y);
	else if (c == 's')
		put_image_spr(game, game->player.spr, x, y + 1);
	else if (c == 'd')
		put_image_spr(game, game->player.spr, x + 1, y);
}

void	move_up(t_game *game)
{
	int	x;
	int	y;

	x = game->player.x;
	y = game->player.y;
	if (game->map.map[y - 1][x] == '0' ||
		game->map.map[y - 1][x] == 'P' ||
		game->map.map[y - 1][x] == 'C')
	{
		move(game, x, y, 'w');
		if (game->map.map[y - 1][x] == 'C')
			element_c(game, 0, -1);
		else
		game->player.y--;
	}
	if (y - 1 == 0)
		lose(game);
	if (game->map.map[y - 1][x] == 'E' && game->collectible.n == 0)
		win(game);
}

void	move_down(t_game *game)
{
	int	x;
	int	y;

	x = game->player.x;
	y = game->player.y;
	if (game->map.map[y + 1][x] == '0' ||
		game->map.map[y + 1][x] == 'P' ||
		game->map.map[y + 1][x] == 'C')
	{
		move(game, x, y, 's');
		if (game->map.map[y + 1][x] == 'C')
			element_c(game, 0, 1);
		else
		game->player.y++;
	}
	if (y + 1 == game->map.h - 1)
		lose(game);
	if (game->map.map[y + 1][x] == 'E' && game->collectible.n == 0)
		win(game);
}

void	move_left(t_game *game)
{
	int	x;
	int	y;

	x = game->player.x;
	y = game->player.y;
	if (game->laserx > game->player.x * game->spr_dim)
		lose(game);
	if (game->map.map[y][x - 1] == '0' ||
		game->map.map[y][x - 1] == 'P' ||
		game->map.map[y][x - 1] == 'C')
	{
		move(game, x, y, 'a');
		if (game->map.map[y][x - 1] == 'C')
			element_c(game, -1, 0);
		else
		game->player.x--;
	}
	if (x - 1 == 0)
		lose(game);
	if (game->map.map[y][x - 1] == 'E' && game->collectible.n == 0)
		win(game);
}

void	move_right(t_game *game)
{
	int	x;
	int	y;

	x = game->player.x;
	y = game->player.y;
	if (game->map.map[y][x + 1] == '0' ||
		game->map.map[y][x + 1] == 'P' ||
		game->map.map[y][x + 1] == 'C')
	{
		move(game, x, y, 'd');
		if (game->map.map[y][x + 1] == 'C')
			element_c(game, 1, 0);
		else
		game->player.x++;
	}
	if (x + 1 == game->map.w - 1)
		lose(game);
	if (game->map.map[y][x + 1] == 'E' && game->collectible.n == 0)
		win(game);
}
