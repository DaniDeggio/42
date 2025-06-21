/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BrickWall.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:53:08 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 01:21:54 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BrickWall.hpp"

		BrickWall::BrickWall() : ATarget("Inconspicuous Red-brick Wall") {
			//std::cout << name << ": This looks like another boring day." << std::endl;
		}
		
		BrickWall::~BrickWall() {
			//std::cout << name << ": My job here is done!" << std::endl;
		}
		
		BrickWall *BrickWall::clone() const {
			return new BrickWall();
		}
		