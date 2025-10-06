/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:23:30 by asacchin          #+#    #+#             */
/*   Updated: 2025/10/04 19:23:59 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ConfigParser.hpp"

ConfigParser::ConfigParser() : _pos(0) {}

ConfigParser::~ConfigParser() {}

void ConfigParser::skipWhitespace() {
    while (_pos < _content.length() && 
           (_content[_pos] == ' ' || _content[_pos] == '\t' || 
            _content[_pos] == '\n' || _content[_pos] == '\r')) {
        _pos++;
    }
}

std::string ConfigParser::getNextToken() {
    skipWhitespace();
    if (_pos >= _content.length()) return "";
    
    size_t start = _pos;
    
    if (_content[_pos] == '"') {
        _pos++;
        start = _pos;
        while (_pos < _content.length() && _content[_pos] != '"') {
            _pos++;
        }
        if (_pos < _content.length()) _pos++;
    } else {
        while (_pos < _content.length() && 
               _content[_pos] != ' ' && _content[_pos] != '\t' && 
               _content[_pos] != '\n' && _content[_pos] != '\r' && 
               _content[_pos] != ';' && _content[_pos] != '{' && 
               _content[_pos] != '}') {
            _pos++;
        }
    }
    
    return _content.substr(start, _pos - start);
}

GlobalConfig ConfigParser::parseConfigFile(const std::string& filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		throw std::runtime_error("Cannot open configuration file: " + filename);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	_content = buffer.str();
	_pos = 0;

	GlobalConfig config;

	while (_pos < _content.length()) {
		skipWhitespace();
		if (_pos >= _content.length()) break;

		std::string token = getNextToken();

		if (token == "server") {
			skipWhitespace();
			if (_pos < _content.length() && _content[_pos] == '{') {
				_pos++;
				ServerConfig server = parseServerBlock();
				config.servers.push_back(server);
			} else {
				throw std::runtime_error("Expected '{' after 'server'");
			}
		} else if (token.empty()) {
			break;
		} else {
			throw std::runtime_error("Unexpected token: " + token);
		}
	}
	return config;
}

ServerConfig ConfigParser::parseServerBlock() {
	ServerConfig server;

	server.port = 80;
	server.host = "localhost";
	server.client_max_body_size = 1048676;

	while (_pos < _content.length()) {
		skipWhitespace();
		if (_pos >= _content.length()) break;

		if (_content[_pos] == '}') {
			_pos++;
			break;
		}

		std::string directive = getNextToken();

		if (directive == "location") {
			std::string path = getNextToken();
			skipWhitespace();
			if (_pos < _content.length() && _content[_pos] == '{') {
				_pos++;
				RouteConfig route = parseLocationBlock(server);
				route.path = path;
				server.routes.push_back(route);
			}
		} else {
			std::string value = getNextToken();
			parseServerDirective(server, directive, value);

			skipWhitespace();
			if (_pos < _content.length() && _content[_pos] == ';') {
				_pos++;
			}
		}
	}
	return server;
}

void ConfigParser::parseServerDirective(ServerConfig& server, const std::string& directive, const std::string& value) {
	if (directive == "listen") {
		server.port = std::atoi(value.c_str());
	} else if (directive == "host") {
		server.host = value;
	} else if (directive == "server_name") {
		server.server_names.push_back(value);

		std::string next;
		while((next = getNextToken()) != "" && next != ";") {
			server.server_names.push_back(next);
		}
		if (next == ";") _pos--;
	} else if (directive == "client_max_body_size") {
		server.client_max_body_size = std::atol(value.c_str());
	} else if (directive == "error_page") {
		int error_code = std::atoi(value.c_str());
		std::string error_file = getNextToken();
		server.error_pages[error_code] = error_file;
	}
}

RouteConfig ConfigParser::parseLocationBlock(ServerConfig& server) {
	RouteConfig route;

	route.directory_listing= false;
	route.methods.push_back("GET");
	route.client_max_body_size = server.client_max_body_size;
	route.cgi_timeout = 120;

	while (_pos < _content.length()) {
		skipWhitespace();
		if (_pos >= _content.length()) break;

		if (_content[_pos] == '}') {
			_pos++;
			break;
		}
		std::string directive = getNextToken();
		std::string value = getNextToken();

		parseLocationDirective(route, directive, value);

		skipWhitespace();
		if (_pos < _content.length() && _content[_pos] == ';')
			_pos++;
	}
	return route;
}

void	ConfigParser::parseLocationDirective(RouteConfig& route, const std::string& directive, const std::string& value) {
	if (directive == "root") {
		route.root = value;
	} else if (directive == "index") {
		route.default_file = value;
	} else if (directive == "autoindex") {
		route.directory_listing = (value == "on");
	} else if (directive == "allow_methods") {
		route.methods.clear();
		route.methods.push_back(value);

		std::string next;
		while ((next = getNextToken()) != "" && next != ";") {
			route.methods.push_back(next);
		}
		if (next == ";") _pos--;
	} else if (directive == "return") {
		route.redirect = value;
	} else if (directive == "cgi_pass") {
		route.cgi_path.clear();
		route.cgi_path.push_back(value);

		std::string next;
		while ((next = getNextToken()) != "" && next != ";") {
			route.cgi_path.push_back(next);
		}
		if (next == ";") _pos--;
	} else if (directive == "cgi_extension") {
		route.cgi_extension.clear();
		route.cgi_extension.push_back(value);

		std::string next;
		while ((next = getNextToken()) != "" && next != ";") {
			route.cgi_extension.push_back(next);
		}
		if (next == ";") _pos--;
	} else if (directive == "cgi_methods") {
		route.cgi_methods.clear();
		route.cgi_methods.push_back(value);

		std::string next;
		while ((next = getNextToken()) != "" && next != ";") {
			route.cgi_methods.push_back(next);
		}
		if (next == ";") _pos--;
	} else if (directive == "upload_pass") {
		route.upload_path = value;
	} else if (directive == "client_max_body_size") {
		route.client_max_body_size = std::atol(value.c_str());
	} else if (directive == "cgi_timeout") {
		route.cgi_timeout = std::atoi(value.c_str());
	}
}