/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:48:55 by dde-giov          #+#    #+#             */
/*   Updated: 2023/05/16 20:45:08 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	put_image_spr2(t_game *game, t_img spr, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win,
		spr.img, x, y);
}

int	laser_anm(t_game *game, int x, int y)
{
	static int	yspr;	

	if (x > game->player.x * game->spr_dim - game->spr_dim / 2)
		return (lose(game));
	if (y % game->spr_dim == 0)
		yspr = y / game->spr_dim;
	if (game->render % game->speed == 0)
	{
		if (yspr != 0 && yspr != game->map.h - 1)
			put_image_spr2(game, game->wall.spr3, x, yspr * game->spr_dim);
		else
		{
			if (yspr == 0)
				put_image_spr2(game, game->wall.spr3,
					x, yspr * game->spr_dim + game->spr_dim / 2);
			else
				put_image_spr2(game, game->wall.spr3,
					x, yspr * game->spr_dim - game->spr_dim / 2);
			put_image_spr2(game, game->wall.spr2,
				x + game->spr_dim / 2, yspr * game->spr_dim);
			put_image_spr2(game, game->wall.spr4, x, yspr * game->spr_dim);
		}
	}
	game->laserx = x;
	return (0);
}

int	space_anm(t_game *game, int x, int y)
{
	static int	xspr;
	static int	yspr;

	if (y % game->spr_dim == 0)
		yspr = y / game->spr_dim;
	if (x % game->spr_dim == 0)
		xspr = x / game->spr_dim;
	if (game->render % game->speed == 0)
	{
		put_image_spr(game, game->ground.spr, xspr, yspr);
		if (x - xspr * game->spr_dim > game->spr_dim / 2)
			put_image_spr(game, game->ground.spr, xspr + 1, yspr);
		put_image_spr(game, game->ground.spr, xspr - 1, yspr);
	}
	return (0);
}

int	animation(t_game *game)
{
	static int	x;
	static int	y;

	if (game->render == 0)
		x = 0;
	if (x < game->map.w * game->spr_dim && game->render >= 0)
	{
		y = 0;
		while (y < game->map.h * game->spr_dim)
		{
			if (space_anm(game, x, y) < 0 || laser_anm(game, x, y) < 0)
				return (-1);
			y += 2;
		}
			y = 0;
	game->render += 1;
	x += 2;
	}
	return (0);
}
