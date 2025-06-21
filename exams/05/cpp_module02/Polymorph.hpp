/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polymorph.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:46:56 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 00:59:37 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLYMORPH_HPP
# define POLYMORPH_HPP

#include <string>
#include <iostream>
#include "ASpell.hpp"

class Polymorph : public ASpell
{
	private:
		Polymorph(Polymorph const &src);
		Polymorph &operator=(Polymorph const &src);

	public:
		Polymorph();
		virtual ~Polymorph();

		virtual Polymorph *clone() const;
};

#endif
