/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:54:02 by dde-giov          #+#    #+#             */
/*   Updated: 2025/01/17 04:18:46 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Bureaucrat.hpp"
#include "../class/AForm.hpp"
#include "../class/ShrubberyCreationForm.hpp"
#include "../class/RobotomyRequestForm.hpp"
#include "../class/PresidentialPardonForm.hpp"
#include "../class/Intern.hpp"

int main(){
	try
	{
		Bureaucrat b1("Bureaucrat1", 120);
		Bureaucrat b2("Bureaucrat2", 140);
		
		AForm *f1 = new ShrubberyCreationForm("TEST");
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
		
		AForm *f1 = new RobotomyRequestForm("TEST");
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
		
		AForm *f1 = new PresidentialPardonForm("TEST");
		b2.signForm(*f1);
		b2.executeForm(*f1);
		b1.executeForm(*f1);
		delete f1;
	} catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	
	std::cout << std::endl;

    try {
        Intern someRandomIntern;
        AForm* rrf;
        

        rrf = someRandomIntern.makeForm("robotomy request", "Bender");
        if (rrf) {
            Bureaucrat b1("Bureaucrat1", 40);
            b1.signForm(*rrf);
            b1.executeForm(*rrf);
            delete rrf;
        }
        
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << std::endl;
}