/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:48:39 by dde-giov          #+#    #+#             */
/*   Updated: 2025/01/08 04:46:19 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm(void) : name("default"), sign(false), gradeToSign(150), gradeToExecute(150) {
	std::cout << "Form default constructor called" << std::endl;
}

AForm::AForm(std::string name, int gradeToSign, int gradeToExecute) : name(name), sign(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute) {
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw AForm::GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw AForm::GradeTooLowException();
	std::cout << "Form constructor called" << std::endl;
}

AForm::AForm(AForm const &src) : name(src.name), sign(src.sign), gradeToSign(src.gradeToSign), gradeToExecute(src.gradeToExecute) {
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw AForm::GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw AForm::GradeTooLowException();
	std::cout << "Form copy constructor called" << std::endl;
}

AForm &AForm::operator=(AForm const &src) {
	if (this != &src) {
		this->sign = src.sign;
	}
	std::cout << "Form assignation operator called" << std::endl;
	return *this;
}

AForm::~AForm(void) {
	std::cout << "Form destructor called" << std::endl;
}

std::string AForm::getName() const{
	return this->name;
}

bool AForm::getSign() const{
	return this->sign;
}

int AForm::getGradeToSign() const{
	return this->gradeToSign;
}

int AForm::getGradeToExecute() const{
	return this->gradeToExecute;
}

void AForm::beSigned(Bureaucrat &b) {
	if (b.getGrade() <= this->gradeToSign)
		this->sign = true;
	else
		throw AForm::GradeTooLowException();
}

void AForm::signAForm(Bureaucrat &b) {
	try
	{
		this->beSigned(b);
		std::cout << b.getName() << " signs " << this->name << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << b.getName() << " cannot sign " << this->name << " because " << e.what() << std::endl;
	}
}

const char* AForm::GradeTooHighException::what() const throw() {
	return "Grade is too high";
}

const char* AForm::GradeTooLowException::what() const throw() {
	return "Grade is too low";
}

std::ostream & operator<<(std::ostream &out, AForm const &frm) {
	out << "Form " << frm.getName() << " is ";
	if (frm.getSign())
		out << "signed";
	else
		out << "not signed";
	out << " and requires grade " << frm.getGradeToSign() << " to sign and grade " << frm.getGradeToExecute() << " to execute" << std::endl;
	return out;
}