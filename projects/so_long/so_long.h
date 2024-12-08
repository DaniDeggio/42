/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:21:24 by dde-giov          #+#    #+#             */
/*   Updated: 2023/05/17 16:05:12 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "minilibx/mlx.h"
# include "get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_map
{
	int		h;
	int		w;
	char	**map;
	char	*path;
}				t_map;

typedef struct s_element
{
	t_img	spr;
	t_img	spr2;
	t_img	spr3;
	t_img	spr4;
	int		x;
	int		y;
	int		n;
}				t_element;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_element	ground;
	t_element	wall;
	t_element	collectible;
	t_element	exit;
	t_element	player;
	int			wins;
	int			retries;
	int			moves;
	int			carburante;
	int			spr_dim;
	int			render;
	int			speed;
	int			col_ini;
	int			playerx;
	int			playery;
	int			laserx;
}				t_game;

//check map
int		check_maph(t_map map);
int		check_mapw(t_map map);
int		check_map_frist_last_line(char *line, t_map map);
int		check_map_letter(char c, int i, int y);
int		check_map_line(char *line, t_map map, int y);

//map utils
void	map_assignetion(t_game *game, char c, int x, int y);
void	map_initelem(t_game *game);
int		check_element_n(t_game *game);
int		map_counter(t_game *game);
void	print_ground(t_game *game, int x);

//map
int		check_ber(char *path);
int		check_map(t_map map);
char	**map_write(t_map map);
void	print_stats(t_game *game);
int		map_init(t_game *game);

//print map
void	put_image_spr(t_game *game, t_img spr, int x, int y);
void	assign(t_game *game, t_img *img, char *path);
void	assign_sprs(t_game *game);
void	put_image_spr_wall(t_game *game, int x, int y);
void	print_map(t_game *game);

//utils
int		ft_close(void);
int		lose(t_game *game);
int		win(t_game *game);
void	print_str(t_game *game, char *str, int n, int x);
void	print_str2(t_game *game, char *str, int n, int x);

//animation
void	put_image_spr2(t_game *game, t_img spr, int x, int y);
int		animation(t_game *game);

//movement
void	move(t_game *game, int x, int y, char c);
void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_right(t_game *game);
void	move_left(t_game *game);

//movement utils
int		key_hook(int key, t_game *game);
void	key_movement(int key, t_game *game);
void	element_c(t_game *game, int x, int y);

int		init(t_game *game);

#endif
