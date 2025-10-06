/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:56:55 by dde-giov          #+#    #+#             */
/*   Updated: 2025/09/06 19:31:33 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Config.hpp"
#include <iostream>

const RouteConfig* ServerConfig::get_route(const std::string& uri) const {
    const RouteConfig* best = NULL;
	size_t bestLen = 0;                       // "/" vale 1

    for (size_t i = 0; i < routes.size(); ++i) {
        const std::string& p = routes[i].path;       // es. "/img"
        if (uri.compare(0, p.length(), p) == 0) {    // prefix match
            if (p.length() > bestLen) {
                best = &routes[i];
                bestLen = p.length();
            }
        }
    }
    return best;
}