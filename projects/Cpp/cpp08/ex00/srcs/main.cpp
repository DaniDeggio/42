/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:59:50 by dde-giov          #+#    #+#             */
/*   Updated: 2025/05/28 19:46:09 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>

#include "../include/easyfind.hpp"

int main( void ) {
	std::vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	
	try {
		std::cout << "Searching 3" << std::endl;
		std::vector<int>::iterator it = easyfind(v, 3);
		std::cout << "Found: 3 in position " << std::distance(v.begin(), it) << std::endl;
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		std::cout << "Searching 5" << std::endl;
		std::vector<int>::iterator it = easyfind(v, 5);
		std::cout << "Found: " << *it << std::endl;
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	
	return 0;
}