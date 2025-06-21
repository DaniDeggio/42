/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fireball.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:46:56 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 00:59:46 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIREBALL_HPP
# define FIREBALL_HPP

#include <string>
#include <iostream>
#include "ASpell.hpp"

class Fireball : public ASpell
{
	private:
		Fireball(Fireball const &src);
		Fireball &operator=(Fireball const &src);

	public:
		Fireball();
		virtual ~Fireball();

		virtual Fireball *clone() const;
};

#endif
