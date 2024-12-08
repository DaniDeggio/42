/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:47:26 by dde-giov          #+#    #+#             */
/*   Updated: 2024/06/18 20:48:52 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string type) {
    this->type = type;
}

Weapon::~Weapon() {
}

const std::string &Weapon::getType() {
    return (this->type);
}

void Weapon::setType(std::string type) {
    this->type = type;
}
