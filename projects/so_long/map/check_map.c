/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:03:58 by dde-giov          #+#    #+#             */
/*   Updated: 2023/04/07 15:37:26 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_maph(t_map map)
{
	int		i;
	int		fd;

	i = 0;
	fd = open(map.path, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd))
	{
		i++;
	}
	return (i);
}

int	check_mapw(t_map map)
{
	int		i;

	i = 0;
	while (map.map[0][i])
	{
		i++;
	}
	return (i);
}

int	check_map_frist_last_line(char *line, t_map map)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
		{
			ft_printf("Error\nMap not closed\n");
			return (-1);
		}
		i++;
	}
	if (ft_strlen(line) != check_mapw(map))
	{
		ft_printf("Error\nInvalid map shape\n");
		return (-1);
	}
	return (1);
}

int	check_map_letter(char c, int i, int y)
{
	if (c != '1' && c != '0' && c != 'C'
		&& c != 'E' && c != 'P')
	{
		ft_printf("Error\nForbidden character: %c\nlocated in line:%d row:%d\n",
			c, y + 1, i + 1);
		return (-1);
	}
	return (1);
}

int	check_map_line(char *line, t_map map, int y)
{
	int	i;

	i = ft_strlen(line);
	i = 0;
	if (ft_strlen(line) != check_mapw(map))
	{
		ft_printf("Error\nInvalid map shape\n");
		return (-1);
	}
	while (line[i])
	{
		if (i == 0 || i == ft_strlen(line) - 1)
		{
			if (line[i] != '1')
			{
				ft_printf("Error\nMap not closed in:\n line:%d row:%d\n",
					y + 1, i + 1);
				return (-1);
			}
		}
		if (check_map_letter(line[i], i, y) < 0)
			return (-1);
		i++;
	}
	return (1);
}
