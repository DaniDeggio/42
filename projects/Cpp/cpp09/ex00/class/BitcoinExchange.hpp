/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:37:49 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/03 05:19:06 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange{
	private:
   		std::map<std::string, double> _rates;

		static bool isValidDate(const std::string& date);
		static bool isLeap(int year);
		static bool parseDouble(const std::string& s, double& out);
		static bool trimSplit(const std::string& line, std::string& date, std::string& valueStr);
		static std::string ltrim(const std::string& s);
		static std::string rtrim(const std::string& s);
		static std::string trim(const std::string& s);
		static void splitOnce(const std::string& s, char sep, std::string& left, std::string& right);
		
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		
		void loadCSV(const std::string& filename);
    	bool getRate(const std::string& date, double& rate) const;
		
	    static bool validLine(const std::string& line, std::string& date, double& value, std::string& errorMsg);
	    static std::string TrimDec(double v);

};

#endif