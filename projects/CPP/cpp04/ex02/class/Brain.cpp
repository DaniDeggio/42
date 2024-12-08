/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:04:56 by dde-giov          #+#    #+#             */
/*   Updated: 2024/09/16 15:10:16 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain() {
    std::cout << "Brain constructor called" << std::endl;
}

Brain::~Brain() {
    std::cout << "Brain destructor called" << std::endl;
}

Brain::Brain(const Brain &src) {
    *this = src;
}

Brain &Brain::operator=(const Brain &src) {
    if (this != &src) {
        for (int i = 0; i < 100; i++)
            this->ideas[i] = src.ideas[i];
    }
    return *this;
}

std::string Brain::getIdea(int i) {
    return this->ideas[i];
}

void Brain::setIdea(int i, std::string idea) {
    this->ideas[i] = idea;
}
