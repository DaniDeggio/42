 
#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include <iostream>
#include <string>

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
	public:
		FragTrap();
		FragTrap(std::string name);
		FragTrap(const FragTrap &src);
		~FragTrap();
		FragTrap &operator=(const FragTrap &src);

		void highFivesGuys();
};

#endif