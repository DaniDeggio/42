/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:35:10 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 00:35:12 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASPELL_HPP
# define ASPELL_HPP

#include <string>
#include <iostream>
#include "ATarget.hpp"

class ATarget;

class ASpell
{
	protected:
		ASpell();
		ASpell(ASpell const &src);
		ASpell &operator=(ASpell const &src);

		std::string name;
		std::string effects;
	public:
		ASpell(std::string const &name, std::string const &effects);
		virtual ~ASpell();

		virtual ASpell *clone() const = 0;
	
		std::string const &getName() const;
		std::string const &getEffects() const;

		void lunchSpell(const ATarget &target) const;
};

#endif
