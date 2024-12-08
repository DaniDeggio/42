/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:54:02 by dde-giov          #+#    #+#             */
/*   Updated: 2024/11/19 21:14:52 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Bureaucrat.hpp"
#include "../class/Form.hpp"

int main(){
	try
	{
		Bureaucrat b1("Bureaucrat1", 2);
		std::cout << b1;
		Form f1("Form1", 2, 2);
		std::cout << f1;
		f1.signForm(b1);
		std::cout << f1;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl; // form too high

	try
	{
		Form f2("Form2", 0, 2);
		std::cout << f2;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl; // form too low

	try
	{
		Form f3("Form3", 2, 151);
		std::cout << f3;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl; // too low to sign

	try
	{
		Bureaucrat b4("Bureaucrat4", 3);
		std::cout << b4;
		Form f4("Form4", 2, 2);
		std::cout << f4;
		f4.signForm(b4);
		std::cout << f4;
		b4.incrementGrade();
		std::cout << b4;
		f4.signForm(b4);
		std::cout << f4;
		b4.incrementGrade();
		std::cout << b4;
		b4.incrementGrade();
		std::cout << b4;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}
