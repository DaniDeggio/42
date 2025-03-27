/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:53:11 by dde-giov          #+#    #+#             */
/*   Updated: 2025/03/27 22:23:53 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

#include <iostream>

template <typename T>
void swap(T &a, T &b) {
	T tmp = a;
	a = b;
	b = tmp;
}

template <typename T>
T const &min(T const &a, T const &b) {
	if (a < b)
		return a;
	return b;
}

template <typename T>
T const &max(T const &a, T const &b) {
	if (a > b)
		return a;
	return b;
}

#endif