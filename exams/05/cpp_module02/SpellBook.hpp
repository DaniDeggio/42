/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpellBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:22:33 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 01:44:45 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPELLBOOK_HPP
# define SPELLBOOK_HPP

#include <string>
#include <iostream>
#include <vector>
#include "ASpell.hpp"

class SpellBook
{
	private:
		SpellBook(SpellBook const &src);
		SpellBook &operator=(SpellBook const &src);

		std::vector<ASpell *> spells;
	
	public:
		SpellBook();
		~SpellBook();
		
		void learnSpell(ASpell *spell);
		void forgetSpell(std::string const &spellName);
		
		ASpell* createSpell(std::string const &spellName) const;
};

#endif