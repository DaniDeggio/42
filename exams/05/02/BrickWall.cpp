/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BrickWall.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:59:17 by ncolomer          #+#    #+#             */
/*   Updated: 2025/06/21 03:17:47 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BrickWall.hpp"

BrickWall::BrickWall():
	ATarget("BrickWall Practice") {}

BrickWall::~BrickWall() {}

ATarget *BrickWall::clone(void) const{
	return(new BrickWall(*this));
}
