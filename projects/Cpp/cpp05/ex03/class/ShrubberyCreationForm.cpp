/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:07:27 by dde-giov          #+#    #+#             */
/*   Updated: 2025/01/08 21:22:17 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void) : AForm("ShrubberyCreationForm", 145, 137) {
	this->target = "default";
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm", 145, 137) {
	this->target = target;
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &src) : AForm(src) {
	this->target = src.target;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &src) {
	if (this != &src) {
		this->target = src.target;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void) {
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const {
	if (executor.getGrade() > this->getGradeToExecute())
		throw AForm::GradeTooLowException();
	if (!this->getSign())
		throw AForm::FormNotSignedException();
	
	std::string Name = this->target;
	Name.append("_shrubbery");
	std::ofstream Out(Name.c_str());
	if (!Out.is_open())
		throw "Error while creating the file: " + this->target + "_shrubbery";
	
	Out << "	           ,@@@@@@@," << std::endl;
	Out << "       ,,,.   ,@@@@@@/@@,  .oo8888o." << std::endl;
	Out << "    ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o" << std::endl;
	Out << "   ,%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'" << std::endl;
	Out << "   %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'" << std::endl;
	Out << "   %&&%/ %&%%&&@@\\ V /@@' `88\\8 `/88'" << std::endl;
	Out << "   `&%\\ ` /%&'    |.|        \\ '|8'" << std::endl;
	Out << "       |o|        | |         | |" << std::endl;
	Out << "       |.|        | |         | |" << std::endl;
	Out << "     \\/ ._\\//_/__/  ,\\_//__\\/.  \\_//__/_" << std::endl;
	Out.close();
}
