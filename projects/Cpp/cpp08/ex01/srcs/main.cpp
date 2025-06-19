/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:59:50 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/19 17:31:43 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../class/Span.hpp"

int main( void ) {
	Span sp = Span(5);

	try {
		sp.addNumber(5);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
	} catch (const std::exception &e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
	std::cout << "Longest span: " << sp.longestSpan() << std::endl;

	std::cout << "Adding a number to full span..." << std::endl;
	try {
		sp.addNumber(6);
	} catch (const std::exception &e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "Searching span with less than 2 elements..." << std::endl;
	Span sp2 = Span(2);
	try {
		std::cout << "Shortest span: " << sp2.shortestSpan() << std::endl;
	} catch
	 (const std::exception &e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	try {
		sp2.addNumber(42);
		std::cout << "Longest span: " << sp2.longestSpan() << std::endl;
	} catch (const std::exception &e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}	

	std::cout << "Testing span with 20.000 elements" << std::endl;
	Span spn = Span(20000);
	for(int i = 0; i < 20000; ++i)
		spn.addNumber(i);

	try {
		std::cout << "Shortest span: " << spn.shortestSpan() << std::endl;
		std::cout << "Longest span: " << spn.longestSpan() << std::endl;
	} catch (const std::exception &e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	return 0;
}