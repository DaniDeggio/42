/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 02:42:08 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/04 18:34:53 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include "Config.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include <iostream>
#include <string>
#include <climits>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <dirent.h>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

class Request;
class Response;
struct ServerConfig;

struct CgiValidation {
    bool ok;
    bool has_sep;
    bool has_ct;
    bool has_loc;
    bool has_status;
};

std::string has_cgi(const Request& request, const ServerConfig* server_config);

std::string to_lower(const std::string& str);
std::string to_upper(const std::string& str);
bool is_subpath(const std::string& full_path, const std::string& base_path);
std::string canon_path(const std::string& path);
std::string normalize_path(const std::string& path);
template<typename T>
std::string to_string(const T& value) {
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

Response serve_file(const std::string& path);
Response serve_autoindex(const std::string& dir,const std::string& uri);

Response error_response(int code, const ServerConfig* server_config);

std::string get_mime_type(const std::string& path);

bool validate_cgi(const std::string& out);

#endif