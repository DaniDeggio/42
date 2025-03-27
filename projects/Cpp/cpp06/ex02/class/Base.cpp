/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:12:41 by dde-giov          #+#    #+#             */
/*   Updated: 2025/03/27 05:16:47 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::~Base(){
	return;
};

Base *Base::generate(void){
	int i = rand() % 3;
	if (i == 0)
		return new A();
	else if (i == 1)
		return new B();
	else
		return new C();
}

void Base::identify(Base* p){
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown" << std::endl;
}

void Base::identify(Base& p){
	try {
		A &a = dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		(void)a;
	
	} catch (std::exception &e) {
		try {
			B &b = dynamic_cast<B&>(p);
			std::cout << "B" << std::endl;
			(void)b;
		} catch (std::exception &e) {
			try {
				C &c = dynamic_cast<C&>(p);
				std::cout << "C" << std::endl;
				(void)c;
			} catch (std::exception &e) {
				std::cout << "Unknown" << std::endl;
			}
		}
	}
	
}