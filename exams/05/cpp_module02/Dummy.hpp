/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dummy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:53:06 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/10 17:57:05 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUMMY_HPP
# define DUMMY_HPP

#include <string>
#include <iostream>
#include "ATarget.hpp"

class Dummy : public ATarget
{
	private:
		Dummy(Dummy const &src);
		Dummy &operator=(Dummy const &src);

	public:
		Dummy();
		virtual ~Dummy();

		virtual Dummy *clone() const;
};

#endif
