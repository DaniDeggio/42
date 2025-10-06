/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserMain.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:57:32 by asacchin          #+#    #+#             */
/*   Updated: 2025/10/04 19:22:44 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ConfigParser.hpp"

int main(int argc, char **argv) {
    try {
        std::string config_file = (argc > 1) ? argv[1] : "webserv.conf";
        
        ConfigParser parser;
        GlobalConfig config = parser.parseConfigFile(config_file);
        
        for (size_t i = 0; i < config.servers.size(); ++i) {
            std::cout << "Server " << i << ": " << config.servers[i].host 
                      << ":" << config.servers[i].port << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Configuration error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
