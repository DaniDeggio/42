/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:29:36 by dde-giov          #+#    #+#             */
/*   Updated: 2023/05/14 16:47:22 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_close(void)
{
	exit(2);
}

int	lose(t_game *game)
{
	game->render = -1;
	print_ground(game, game->map.w);
	mlx_string_put(game->mlx, game->win, game->spr_dim * (game->map.w / 2 - 1),
		game->spr_dim * game->map.h / 2, 0xFFFFFFFF, "You lose");
	mlx_string_put(game->mlx, game->win, game->spr_dim * (game->map.w / 2 - 1),
		game->spr_dim * (game->map.h + 1) / 2, 0xFFFFFFFF, "Press R to retry");
	mlx_string_put(game->mlx, game->win, game->spr_dim * (game->map.w / 2 - 1),
		game->spr_dim * (game->map.h + 2) / 2, 0xFFFFFFFF, "Press Esc to exit");
	print_str(game, "Total retries: ", game->retries, game->map.w / 2 - 1);
	return (-1);
}

int	win(t_game *game)
{
	game->render = -1;
	mlx_string_put(game->mlx, game->win, game->spr_dim * game->map.w / 2,
		game->spr_dim * game->map.h / 2, 0xFFFFFFFF, "You win");
	mlx_string_put(game->mlx, game->win, game->spr_dim * (game->map.w / 2 - 1),
		game->spr_dim * (game->map.h + 1) / 2, 0xFFFFFFFF, "Press Esc to exit");
	print_str(game, "Total retries: ", game->retries, game->map.w / 2 - 1);
	game->win += 1;
	return (-1);
}

void	print_str(t_game *game, char *str, int n, int x)
{
	int	i;
	int	spr4;

	spr4 = game->spr_dim / 4;
	i = ft_strlen(str) / 5;
	mlx_string_put(game->mlx, game->win, game->spr_dim * x,
		((game->map.h + 1) * game->spr_dim) - spr4 * 3,
		0xFFFFFFFF, str);
	if (n >= 0)
		mlx_string_put(game->mlx, game->win, game->spr_dim * x
			+ game->spr_dim * i, ((game->map.h + 1)
				* game->spr_dim) - spr4 * 3,
			0xFFFFFFFF, ft_itoa(n));
}

void	print_str2(t_game *game, char *str, int n, int x)
{
	int	i;
	int	spr4;

	spr4 = game->spr_dim / 4;
	i = ft_strlen(str) / 5;
	mlx_string_put(game->mlx, game->win, game->spr_dim * x,
		((game->map.h + 1) * game->spr_dim) - spr4,
		0xFFFFFFFF, str);
	if (n >= 0)
		mlx_string_put(game->mlx, game->win, game->spr_dim * x
			+ game->spr_dim * i, ((game->map.h + 1)
				* game->spr_dim) - spr4,
			0xFFFFFFFF, ft_itoa(n));
}
