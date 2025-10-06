#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

# include "Config.hpp"
# include <fstream>
# include <sstream>
# include <stdlib.h>
# include <stdio.h>
# include <iostream>
# include <stdlib.h>

class ConfigParser {
private:
	std::string _content;
	size_t _pos;

	// Metodi helper per il parsing
	void		skipWhitespace();
	std::string	getNextToken();
	std::string	getNextLine();
	bool		isValidDirective(const std::string& directive);

	// Metodi per parsare i blocchi
	ServerConfig parseServerBlock();
	RouteConfig	parseLocationBlock(ServerConfig& server);

	// Metodi per parsare le singole direttive
	void	parseServerDirective(ServerConfig& server, const std::string& directive, const std::string& value);
	void	parseLocationDirective(RouteConfig& route, const std::string& directive, const std::string& value);

public:
	ConfigParser();
    ~ConfigParser();

	GlobalConfig parseConfigFile(const std::string& filename);
	void printConfig(const GlobalConfig& config);

};

#endif