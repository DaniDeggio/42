/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:12:41 by dde-giov          #+#    #+#             */
/*   Updated: 2025/01/17 04:14:17 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern(void){
}

Intern::Intern(Intern const &src){
	(void)src;
}

Intern &Intern::operator=(Intern const &src) {
	(void)src;
	return *this;
}

Intern::~Intern(void) {
}

AForm *Intern::SCForm(std::string target) {
	return new ShrubberyCreationForm(target);
}

AForm *Intern::RRForm(std::string target) {
	return new RobotomyRequestForm(target);
}

AForm *Intern::PPForm(std::string target) {
	return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(std::string name, std::string target) {
	std::string names[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};
	AForm *(Intern::*formFuncs[3])(std::string) = {&Intern::SCForm, &Intern::RRForm, &Intern::PPForm};

	for (int i = 0; i < 3; i++) {
		if (names[i] == name) {
			std::cout << "Intern creates " << name << std::endl;
			return (this->*formFuncs[i])(target);
		}
	}
	std::cout << "Intern cannot create " << name << std::endl;
	return NULL;
}