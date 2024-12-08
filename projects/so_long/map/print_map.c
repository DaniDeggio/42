/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:48:47 by dde-giov          #+#    #+#             */
/*   Updated: 2023/05/17 15:29:41 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	put_image_spr(t_game *game, t_img spr, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win,
		spr.img, x * game->spr_dim, y * game->spr_dim);
}

void	assign(t_game *game, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx,
			path, &game->spr_dim, &game->spr_dim);
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pixel,
			&img->line_length,
			&img->endian);
}

void	assign_sprs(t_game *game)
{
	assign(game, &game->ground.spr, "sprs/background.xpm");
	assign(game, &game->wall.spr, "sprs/wall.xpm");
	assign(game, &game->wall.spr2, "sprs/orizzontali.xpm");
	assign(game, &game->wall.spr3, "sprs/verticali.xpm");
	assign(game, &game->wall.spr4, "sprs/generatori.xpm");
	assign(game, &game->collectible.spr, "sprs/collectible.xpm");
	assign(game, &game->exit.spr, "sprs/exit.xpm");
	assign(game, &game->player.spr, "sprs/player.xpm");
}

void	put_image_spr_wall(t_game *game, int x, int y)
{
	if ((x > 0 && x < game->map.w - 1) && (y == 0 || y == game->map.h - 1))
		put_image_spr(game, game->wall.spr2, x, y);
	else if ((x == 0 || x == game->map.w - 1) && (y > 0 && y < game->map.h - 1))
		put_image_spr(game, game->wall.spr3, x, y);
	else if (x == 0 || x == game->map.w - 1)
	{
		if (x == 0)
			put_image_spr2(game, game->wall.spr2, x * game->spr_dim
				+ game->spr_dim / 2, y * game->spr_dim);
		else
			put_image_spr2(game, game->wall.spr2, x * game->spr_dim
				- game->spr_dim / 2, y * game->spr_dim);
		if (y == 0)
			put_image_spr2(game, game->wall.spr3, x * game->spr_dim,
				y * game->spr_dim + game->spr_dim / 2);
		else
			put_image_spr2(game, game->wall.spr3, x * game->spr_dim,
				y * game->spr_dim - game->spr_dim / 2);
		put_image_spr(game, game->wall.spr4, x, y);
	}
	else
		put_image_spr(game, game->wall.spr, x, y);
}

void	print_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	game->render = 0;
	while (i < game->map.h)
	{
		while (j < game->map.w)
		{
			if (game->map.map[i][j] == '1')
				put_image_spr_wall(game, j, i);
			else if (game->map.map[i][j] == 'P')
				put_image_spr(game, game->player.spr, j, i);
			else if (game->map.map[i][j] == 'E')
				put_image_spr(game, game->exit.spr, j, i);
			else if (game->map.map[i][j] == 'C')
				put_image_spr(game, game->collectible.spr, j, i);
			j++;
		}
		j = 0;
		i++;
	}
}
