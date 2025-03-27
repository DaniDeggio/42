/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 05:17:39 by dde-giov          #+#    #+#             */
/*   Updated: 2025/01/21 05:53:48 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
# define BASE_HPP

#include <iostream>
#include <string>
#include <cstdlib>


class Base {
	private:	
		
	public:
		virtual ~Base();

		static Base *generate(void);
		static void identify(Base* p);
		static void identify(Base& p);
}; 

#endif