/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:37:49 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/19 17:58:15 by dde-giov         ###   ########.fr       */
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
		throw std::length_error("Span is full");
	n.push_back(numb);
}

int Span::shortestSpan() const {
	if (n.size() < 2)
		throw std::logic_error("Not enough elements to find a span");

	unsigned int minSpan;
	unsigned int span;
	
	std::vector<int> sorted = n;
	std::sort(sorted.begin(), sorted.end());

	for (size_t i = 0; i < sorted.size() - 1; ++i) {
		span = sorted[i + 1] - sorted[i];

		if (i == 0 || span < minSpan)
			minSpan = span;
	}

	return minSpan;
}

int Span::longestSpan() const {
	if (n.size() < 2)
		throw std::logic_error("Not enough elements to find a span");

	int min;
	int max;
	
	min = *std::min_element(n.begin(), n.end());
	max = *std::max_element(n.begin(), n.end());

	return max - min;
}