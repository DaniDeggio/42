/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:12:41 by dde-giov          #+#    #+#             */
/*   Updated: 2025/01/08 19:41:07 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void) : AForm("PresidentialPardonForm", 25, 5) {
	this->target = "default";
}

PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("PresidentialPardonForm", 25, 5) {
	this->target = target;	
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &src) : AForm(src) {
	this->target = src.target;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(PresidentialPardonForm const &src) {
	if (this != &src) {
		this->target = src.target;
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm(void) {
}

void PresidentialPardonForm::execute(Bureaucrat const & executor) const {
	if (executor.getGrade() > this->getGradeToExecute())
		throw AForm::GradeTooLowException();
	if (!this->getSign())
		throw AForm::FormNotSignedException();
	std::cout << this->target << " has been pardoned by Zafod Beeblebrox" << std::endl;
}
