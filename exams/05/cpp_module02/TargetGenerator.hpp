/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TargetGenerator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:22:33 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 01:51:59 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TARGETGENERATOR_HPP
# define TARGETGENERATOR_HPP

#include <string>
#include <iostream>
#include <vector>
#include "ATarget.hpp"

class TargetGenerator
{
	private:
		TargetGenerator(TargetGenerator const &src);
		TargetGenerator &operator=(TargetGenerator const &src);

		std::vector<ATarget *> targets;
	
	public:
		TargetGenerator();
		~TargetGenerator();
		
		void learnTargetType(ATarget*);
		void forgetTargetType(std::string const &targetType);
		ATarget* createTarget(std::string const &targetType);
};

#endif