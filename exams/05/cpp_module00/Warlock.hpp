/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:22:33 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/10 16:29:38 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
# define WARLOCK_HPP

#include <string>
#include <iostream>

class Warlock
{
	private:
		Warlock();
		Warlock(Warlock const &src);
		Warlock &operator=(Warlock const &src);

		std::string name;
		std::string title;
	public:
		Warlock(std::string const &name, std::string const &title);
		~Warlock();
		
		std::string const &getName() const;
		std::string const &getTitle() const;
		
		void setTitle(std::string const &title);

		void introduce() const;
};

#endif