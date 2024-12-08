/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:16:17 by dde-giov          #+#    #+#             */
/*   Updated: 2023/05/16 16:33:05 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	key_hook(int key, t_game *game)
{
	if (key == 53)
		ft_close();
	if (key == 15)
	{
		game->retries++;
		map_counter(game);
		map_init(game);
		init(game);
		print_map(game);
	}
	if (((key > 122 && key < 127) || (key >= 0 && key < 3) || key == 13)
		&& game->carburante > 0 && game->render >= 0)
		key_movement(key, game);
	if (game->carburante <= 0)
		game->speed += 2;
	if (game->speed > 15)
		game->speed = 15;
	return (1);
}

void	key_movement(int key, t_game *game)
{
	if (key == 126 || key == 13)
		move_up(game);
	if (key == 123 || key == 0)
		move_left(game);
	if (key == 125 || key == 1)
		move_down(game);
	if (key == 124 || key == 2)
		move_right(game);
	print_stats(game);
}

void	element_c(t_game *game, int x, int y)
{
	game->player.x += x;
	game->player.y += y;
	game->carburante += game->map.w / 5 + 2;
	game->collectible.n--;
	if (game->collectible.n < game->col_ini / 2)
		game->speed += 2;
}
