/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:14:00 by dde-giov          #+#    #+#             */
/*   Updated: 2023/02/08 16:52:46 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *format, ...);
int		ft_conversions(va_list vlist, const char c);
size_t	ft_printhex(size_t nbr, char c);
size_t	ft_printchar(char c);
size_t	ft_printstr(char *str);
size_t	ft_printpointer(void *ptr);
size_t	ft_printnbr(int nbr);
size_t	ft_printunbr(unsigned int nbr);

#endif