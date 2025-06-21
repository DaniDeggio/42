#ifndef WARLOCK_HPP
# define WARLOCK_HPP

#include <string>
#include <iostream>
#include <vector>

#include "ASpell.hpp"
#include "ATarget.hpp"

class ASpell;
class ATarget;

class Warlock{
	private:
		std::string name;
		std::string title;

		std::vector<ASpell *> spells;
	
		Warlock();
		Warlock(Warlock const &src);
		Warlock &operator=(Warlock const &src);
	public:
		Warlock(std::string const &name, std::string const &title);
		~Warlock();
		
		std::string const &getName() const;
		std::string const &getTitle() const;

		void setTitle(std::string const &ttl);
		void introduce() const;

		void learnSpell(ASpell *spell);
		void forgetSpell(std::string const &spell);
		void launchSpell(std::string const &spell, ATarget const &target);
};

#endif