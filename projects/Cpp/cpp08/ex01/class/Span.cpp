/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:37:49 by dde-giov          #+#    #+#             */
/*   Updated: 2025/05/31 15:50:08 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(void){
}

Span::Span(unsigned int n) : maxSize(n) {
}

Span::Span(const Span &src) : n(src.n), maxSize(src.maxSize) {
}

Span::~Span(void) {
}

Span &Span::operator=(const Span &src){
	if (this != &src) {
		this->n = src.n;
		this->maxSize = src.maxSize;
	}

	return *this;
}

void Span::addNumber(int numb) {
	if (n.size() >= maxSize)
		throw std::exception("Span is full, cannot add more numbers.");
	n.push_back(numb);
}

int Span::shortestSpan() const {
	if (n.sized < 2)
		throw std::exception("Not enough numbers to find a span.");
	
	
}
