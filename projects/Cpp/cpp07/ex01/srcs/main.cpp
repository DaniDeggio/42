/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:59:50 by dde-giov          #+#    #+#             */
/*   Updated: 2025/03/27 22:48:03 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../include/iter.hpp"

void increment(int &n) {
	n++;
}

void doubleValue(int &n) {
	n *= 2;
}

int main( void ) {
	int even[] = {2, 4, 6, 8, 10};

	std::cout << "Even numbers: ";
	for (int i = 0; i < 5; i++) {
		std::cout << even[i] << ", ";
	}
	std::cout << std::endl;

	iter(even, 5, increment);
	
	std::cout << "Even numbers incremented by 1: ";
	for (int i = 0; i < 5; i++) {
		std::cout << even[i] << ", ";
	}
	std::cout << std::endl;
	
	iter(even, 5, doubleValue);
	
	std::cout << "Odd numbers doubled: ";
	for (int i = 0; i < 5; i++) {
		std::cout << even[i] << ", ";
	}
	std::cout << std::endl;
	
	return 0;
}