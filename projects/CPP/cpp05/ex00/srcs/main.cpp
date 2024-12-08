/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:54:02 by dde-giov          #+#    #+#             */
/*   Updated: 2024/11/19 20:03:44 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Bureaucrat.hpp"

int main(){
	// increment
	try
	{
		Bureaucrat b1("Bureaucrat1", 2);
		std::cout << b1;
		b1.incrementGrade();
		std::cout << b1;
		b1.incrementGrade();
		std::cout << b1;
		
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	
	std::cout << std::endl; // decrement
	try
	{
		Bureaucrat b2("Bureaucrat2", 149);
		std::cout << b2;
		b2.decrementGrade();
		std::cout << b2;
		b2.decrementGrade();
		std::cout << b2;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl; // too high
	try
	{
		Bureaucrat b3("Bureaucrat3", 0);
		std::cout << b3;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	
	std::cout << std::endl; // too low
	try
	{
		Bureaucrat b4("Bureaucrat4", 151);
		std::cout << b4;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}