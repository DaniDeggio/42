/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:53:46 by dde-giov          #+#    #+#             */
/*   Updated: 2024/07/04 16:48:31 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <string>

class Fixed {
	private:
		int	fx_value;
		static const int	fract = 8;
	public:
		Fixed(void);
		Fixed(const Fixed &fx);
		Fixed &operator=(const Fixed &fx);
		~Fixed(void);

		int getRawBits( void ) const;
		void setRawBits( int const raw );

};

#endif