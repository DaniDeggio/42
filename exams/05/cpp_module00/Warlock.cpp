/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:27:44 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/10 16:46:45 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"

		Warlock::Warlock(std::string const &name, std::string const &title) : name(name), title(title){
			std::cout << name << ": This looks like another boring day." << std::endl;
		}

		Warlock::~Warlock() {
			std::cout << name << ": My job here is done!" << std::endl;
		}
		
		std::string const &Warlock::getName() const {
			return name;
		}
		
		std::string const &Warlock::getTitle() const {
			return title;
		}

		void Warlock::setTitle(std::string const &title) {
			this->title = title;
		}

		void Warlock::introduce() const {
			std::cout << name << ": I am " << name << ", " << title << "!" << std::endl;
		}