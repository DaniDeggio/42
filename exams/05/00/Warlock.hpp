#ifndef WARLOCK_HPP
# define WARLOCK_HPP

#include <string>
#include <iostream>

class Warlock{
	private:
		std::string name;
		std::string title;

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
};

#endif