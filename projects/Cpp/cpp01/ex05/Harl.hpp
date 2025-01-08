/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:18:24 by dde-giov          #+#    #+#             */
/*   Updated: 2024/10/13 17:12:10 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

#include <string>
#include <iostream>

class Harl{
    private:
        void debug(void);
        void info(void);
        void warning(void);
        void error(void);

    public:
        void complain(std::string level);
};

#endif