/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:07:17 by dde-giov          #+#    #+#             */
/*   Updated: 2025/01/09 16:18:39 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include "AForm.hpp"

class AForm;

class Bureaucrat {
	private:
		const std::string name;
		int grade;

	public:
		Bureaucrat(void);
		Bureaucrat(std::string name);
		Bureaucrat(int grade);
		Bureaucrat(std::string name, int grade);

		~Bureaucrat(void);
		Bureaucrat(Bureaucrat const &src);
		Bureaucrat &operator=(Bureaucrat const &src);

		std::string getName() const;
		int getGrade() const;

		void incrementGrade();
		void decrementGrade();

		void signForm(AForm & form);
		void executeForm(AForm const & form);

		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		
		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

std::ostream & operator<<(std::ostream &out, Bureaucrat const &src);

#endif