/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dummy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:53:08 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 00:39:32 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dummy.hpp"

		Dummy::Dummy() : ATarget("Target Practice Dummy") {
			//std::cout << name << ": This looks like another boring day." << std::endl;
		}

		Dummy::~Dummy() {
			//std::cout << name << ": My job here is done!" << std::endl;
		}
		
		Dummy *Dummy::clone() const {
			return new Dummy();
		}
		