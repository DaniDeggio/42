/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:22:33 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/10 18:01:37 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
# define WARLOCK_HPP

#include <string>
#include <iostream>
#include <vector>
#include "ASpell.hpp"

class Warlock
{
	private:
		Warlock();
		Warlock(Warlock const &src);
		Warlock &operator=(Warlock const &src);

		std::string name;
		std::string title;
		std::vector<ASpell *> spells;

	public:
		Warlock(std::string const &name, std::string const &title);
		~Warlock();
		
		std::string const &getName() const;
		std::string const &getTitle() const;
		
		void setTitle(std::string const &title);

		void introduce() const;
		void learnSpell(ASpell *spell);
		void forgetSpell(std::string const &spellName);
		void launchSpell(std::string const &spellName, ATarget &target) const;
};

#endif