/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:37:49 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/19 17:58:45 by dde-giov         ###   ########.fr       */
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

		template <typename IT>
		void addNumbers(IT frist, IT last){
			size_t numbs = std::distance(frist, last);

			if (this->n.size() + numbs > this->maxSize)
				throw std::length_error("trying to add too many elements");
			std::copy(frist, last, std::back_inserter(this->n));
		}

};

#endif