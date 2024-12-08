/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:44:32 by dde-giov          #+#    #+#             */
/*   Updated: 2023/05/14 16:51:12 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init(t_game *game)
{
	game->carburante = game->map.w / 4 + 2;
	game->speed = 1;
	print_ground(game, game->map.w);
	print_map(game);
	print_stats(game);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		ft_printf("Error\n Select one map file");
		return (-1);
	}
	game = malloc(sizeof(t_game));
	if (!game)
		return (-1);
	game->map.path = argv[1];
	if (map_init(game) < 0)
		return (-1);
	game->spr_dim = 64;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, (game->map.w)
			* game->spr_dim, (game->map.h + 1) * game->spr_dim, "so_long");
	mlx_hook(game->win, 17, 0, ft_close, 0);
	assign_sprs(game);
	init(game);
	mlx_key_hook(game->win, key_hook, (void *)game);
	mlx_loop_hook(game->mlx, animation, (void *)game);
	mlx_loop(game->mlx);
	return (0);
}
