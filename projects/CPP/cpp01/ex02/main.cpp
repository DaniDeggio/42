/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:05:19 by dde-giov          #+#    #+#             */
/*   Updated: 2024/06/18 22:25:47 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

int main(void) {
	std::string stringg = "HI THIS IS BRAIN";
	std::string	*stringPTR = &stringg;
	std::string &stringREF = stringg;

	std::cout <<  "Memory address of the string variable: " << &stringg << std::endl;
	std::cout <<  "Memory address held by stringPTR: " << stringPTR << std::endl;
	std::cout <<  "Memory address held by stringREF: " << &stringREF << std::endl;

	std::cout << "Value of the string variable: " << stringg << std::endl;
	std::cout << "Value pointed to by stringPTR: " << *stringPTR << std::endl;
	std::cout << "Value pointed to by stringREF: " << stringREF << std::endl;
	return 0;
}
