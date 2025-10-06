/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:03:03 by dde-giov          #+#    #+#             */
/*   Updated: 2025/09/09 16:54:10 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "Config.hpp"
#include "utils.hpp"
#include <string>
#include <map>
#include <sstream>

class Response {
	private:
		int status_code;
		std::string status_text;
		std::map<std::string, std::string> headers;
		std::string body;
	public:
		Response();
		Response(int code, const std::string& text);
		
		void stock_status(int code);
		void set_status(int code);
		void set_status_text(const std::string& text);
		void add_header(const std::string& key, const std::string& value);
		void set_body(const std::string& content);
		std::string get_status_line() const;
		int get_code() const;

		void parse_cgi_response(const std::string& cgi_output, const ServerConfig* server_config);
		
		std::string to_string(); // genera la stringa da mandare al client
		std::string get_header(const std::string& key) const;
};

#endif