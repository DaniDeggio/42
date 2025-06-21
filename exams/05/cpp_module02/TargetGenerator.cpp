/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TargetGenerator.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:27:44 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 01:59:18 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TargetGenerator.hpp"

		TargetGenerator::TargetGenerator() {
			// 
		}

		TargetGenerator::~TargetGenerator() {
			//
		}
	
		void TargetGenerator::learnTargetType(ATarget *target) {
			if (target)
				targets.push_back(target->clone());
		}

		void TargetGenerator::forgetTargetType(std::string const &targetType) {
			std::vector<ATarget *>::iterator it = targets.begin();
			for (; it != targets.end(); ) {
				if ((*it)->getType() == targetType) {
					delete *it;
					it = targets.erase(it);
				}
			}
		}

		ATarget* TargetGenerator::createTarget(std::string const &targetType) {
			std::vector<ATarget *>::const_iterator it = targets.begin();
			for (; it != targets.end(); ++it) {
				if ((*it)->getType() == targetType)
					return (*it)->clone();
			}
			return NULL;
		}
