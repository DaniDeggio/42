/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:37:49 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/03 16:23:22 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>

class Span{
	private:
		std::vector<int> n;
		unsigned int maxSize;
	
		Span();
	public:
		Span(unsigned int n);
		Span(const Span &src);
		~Span();

		Span &operator=(const Span &src);

		void addNumber(int numb);
		int shortestSpan() const;
		int longestSpan() const;
};

#endif