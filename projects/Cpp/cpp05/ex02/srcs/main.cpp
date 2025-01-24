/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:54:02 by dde-giov          #+#    #+#             */
/*   Updated: 2025/01/09 16:05:35 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Bureaucrat.hpp"
#include "../class/AForm.hpp"
#include "../class/ShrubberyCreationForm.hpp"
#include "../class/RobotomyRequestForm.hpp"
#include "../class/PresidentialPardonForm.hpp"

int main(int ac, char **av){
	std::string target("Default");
	if (ac > 1)
		target = av[1];

	try
	{
		Bureaucrat b1("Bureaucrat1", 120);
		Bureaucrat b2("Bureaucrat2", 140);
		
		AForm *f1 = new ShrubberyCreationForm(target);
		b2.signForm(*f1);
		b2.executeForm(*f1);
		b1.executeForm(*f1);
		
		delete f1;
	} catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	
	std::cout << std::endl;

	try
	{
		Bureaucrat b1("Bureaucrat1", 40);
		Bureaucrat b2("Bureaucrat2", 60);
		
		AForm *f1 = new RobotomyRequestForm(target);
		b2.signForm(*f1);
		b2.executeForm(*f1);
		b1.executeForm(*f1);
		delete f1;
	} catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	
	std::cout << std::endl;

	try
	{
		Bureaucrat b1("Bureaucrat1", 10);
		Bureaucrat b2("Bureaucrat2", 2);
		
		AForm *f1 = new PresidentialPardonForm(target);
		b2.signForm(*f1);
		b2.executeForm(*f1);
		b1.executeForm(*f1);
		delete f1;
	} catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	
	std::cout << std::endl;
}