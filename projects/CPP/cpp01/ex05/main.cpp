/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:18:01 by dde-giov          #+#    #+#             */
/*   Updated: 2024/07/01 14:37:08 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int ac, char **av){
	Harl test;
	
	if (ac == 1){
		test.complain("DEBUG");
		std::cout << std::endl;
		test.complain("INFO");
		std::cout << std::endl;
		test.complain("WARNING");
		std::cout << std::endl;
		test.complain("ERROR");
		std::cout << std::endl;
	}
	else {
		test.complain(av[1]);
	}
}