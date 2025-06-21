/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:37:34 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 00:37:48 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:35:10 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/10 17:37:25 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATARGET_HPP
# define ATARGET_HPP

#include <string>
#include <iostream>
#include "ASpell.hpp"

class ASpell;

class ATarget
{
	protected:
		ATarget(ATarget const &src);
		ATarget &operator=(ATarget const &src);

		std::string type;
	public:
		ATarget(std::string const &type);
		virtual ~ATarget();

		virtual ATarget *clone() const = 0;
	
		std::string const &getType() const;
		void getHitBySpell(const ASpell &spell) const;
};

#endif
