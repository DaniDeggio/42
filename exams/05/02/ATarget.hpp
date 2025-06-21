#ifndef ATARGET_HPP
# define ATARGET_HPP

#include <string>
#include <iostream>
#include "ASpell.hpp"

class ASpell;

class ATarget{
	protected:
		std::string type;

	public:
		ATarget();
		ATarget(std::string const &type);
		ATarget(ATarget const &src);
		ATarget &operator=(ATarget const &src);
		virtual ~ATarget();
		
		virtual ATarget *clone() const = 0;
		
		std::string const &getType() const;

		void getHitBySpell(ASpell const &spell) const;
	};

#endif