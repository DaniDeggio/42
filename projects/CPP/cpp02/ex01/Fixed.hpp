/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:53:46 by dde-giov          #+#    #+#             */
/*   Updated: 2024/07/04 19:53:38 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <string>
#include <cmath>

class Fixed {
	private:
		int	fx_value;
		static const int	fract = 8;
	public:
		Fixed(void);
		Fixed(const Fixed &fx);
		Fixed(const int value);
		Fixed(const float value);
		Fixed &operator=(const Fixed &fx);
		~Fixed(void);

		int getRawBits( void ) const;
		void setRawBits( int const raw );
		float toFloat( void ) const;
		int toInt( void ) const;
		

};
std::ostream & operator<<(std::ostream &out, const Fixed &fx);

#endif