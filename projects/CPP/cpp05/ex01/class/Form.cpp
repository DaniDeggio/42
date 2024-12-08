/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:48:39 by dde-giov          #+#    #+#             */
/*   Updated: 2024/11/19 21:04:10 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(void) : name("default"), sign(false), gradeToSign(150), gradeToExecute(150) {
	std::cout << "Form default constructor called" << std::endl;
}

Form::Form(std::string name, int gradeToSign, int gradeToExecute) : name(name), sign(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute) {
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw Form::GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw Form::GradeTooLowException();
	std::cout << "Form constructor called" << std::endl;
}

Form::Form(Form const &src) : name(src.name), sign(src.sign), gradeToSign(src.gradeToSign), gradeToExecute(src.gradeToExecute) {
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw Form::GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw Form::GradeTooLowException();
	std::cout << "Form copy constructor called" << std::endl;
}

Form &Form::operator=(Form const &src) {
	if (this != &src) {
		this->sign = src.sign;
	}
	std::cout << "Form assignation operator called" << std::endl;
	return *this;
}

Form::~Form(void) {
	std::cout << "Form destructor called" << std::endl;
}

std::string Form::getName() const{
	return this->name;
}

bool Form::getSign() const{
	return this->sign;
}

int Form::getGradeToSign() const{
	return this->gradeToSign;
}

int Form::getGradeToExecute() const{
	return this->gradeToExecute;
}

void Form::beSigned(Bureaucrat &b) {
	if (b.getGrade() <= this->gradeToSign)
		this->sign = true;
	else
		throw Form::GradeTooLowException();
}

void Form::signForm(Bureaucrat &b) {
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

const char* Form::GradeTooHighException::what() const throw() {
	return "Grade is too high";
}

const char* Form::GradeTooLowException::what() const throw() {
	return "Grade is too low";
}

std::ostream & operator<<(std::ostream &out, Form const &frm) {
	out << "Form " << frm.getName() << " is ";
	if (frm.getSign())
		out << "signed";
	else
		out << "not signed";
	out << " and requires grade " << frm.getGradeToSign() << " to sign and grade " << frm.getGradeToExecute() << " to execute" << std::endl;
	return out;
}