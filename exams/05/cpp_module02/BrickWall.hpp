/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BrickWall.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:53:06 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 01:00:51 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRICKWALL_HPP
# define BRICKWALL_HPP

#include <string>
#include <iostream>
#include "ATarget.hpp"

class BrickWall : public ATarget
{
	private:
		BrickWall(BrickWall const &src);
		BrickWall &operator=(BrickWall const &src);

	public:
		BrickWall();
		virtual ~BrickWall();

		virtual BrickWall *clone() const;
};

#endif
