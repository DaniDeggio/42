/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:04:52 by dde-giov          #+#    #+#             */
/*   Updated: 2024/11/03 22:20:53 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>
# include <string>

class Brain {
	public:
		Brain();
		~Brain();
		Brain(const Brain &src);
		Brain &operator=(const Brain &src);

		std::string getIdea(int i);
		void setIdea(int i, std::string idea);
	private:
		std::string ideas[100];
};

#endif