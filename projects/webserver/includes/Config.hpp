/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:18:45 by dde-giov          #+#    #+#             */
/*   Updated: 2025/09/29 00:29:49 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>
#include <map>

// Configurazione di una singola route
struct RouteConfig {
    std::string path;                      // Es: "/images"
    std::string root;                      // Es: "/var/www/images"
    bool directory_listing;                // true/false
    std::string default_file;              // Es: "index.html"
    std::vector<std::string> methods;      // Es: {"GET", "POST"}
    std::string redirect;                  // Es: "http://example.com"
    std::vector<std::string> cgi_extension;  // Es: ".php"
    std::vector<std::string> cgi_path;    // Es: "/usr/bin/php-cgi"
    std::vector<std::string> cgi_methods;      // Es: {"GET", "POST"}
	int cgi_timeout;                       // Es: 120 (secondi)
    std::string upload_path;               // Es: "/var/uploads"
	size_t client_max_body_size;           // Es: 1048576 (1MB)
};

// Configurazione di un server virtuale
struct ServerConfig {
    int port;                              // Es: 8080
    std::string host;                      // Es: "localhost"
    std::vector<std::string> server_names; // Es: {"example.com", "www.example.com"}
    std::map<int, std::string> error_pages;// Es: {404: "errors/404.html"}
    size_t client_max_body_size;           // Es: 1048576 (1MB)
    std::vector<RouteConfig> routes;       // Lista di route

	const RouteConfig* get_route(const std::string& uri) const;
};

// Configurazione globale
struct GlobalConfig {
    std::vector<ServerConfig> servers;     // Multipli server supportati
};

#endif