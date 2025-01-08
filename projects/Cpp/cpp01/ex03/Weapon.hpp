/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:39:43 by dde-giov          #+#    #+#             */
/*   Updated: 2024/10/13 16:58:45 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <string>

class Weapon {
    private:
        std::string type;

    public:
        Weapon(std::string type);
        ~Weapon();

        const std::string &getType();
        void setType(std::string type);
};

#endif