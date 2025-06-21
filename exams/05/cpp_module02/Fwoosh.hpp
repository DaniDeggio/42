/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fwoosh.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:46:56 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/10 17:49:23 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FWOOSH_HPP
# define FWOOSH_HPP

#include <string>
#include <iostream>
#include "ASpell.hpp"

class Fwoosh : public ASpell
{
	private:
		Fwoosh(Fwoosh const &src);
		Fwoosh &operator=(Fwoosh const &src);

	public:
		Fwoosh();
		virtual ~Fwoosh();

		virtual Fwoosh *clone() const;
};

#endif
