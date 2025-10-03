/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:59:50 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/03 05:24:16 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange ex;
    ex.loadCSV("data.csv");

    std::ifstream in(argv[1]);
    if (!in) {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty())
			continue;

        std::string date;
        double value = 0.0;
        std::string err;

        if (!BitcoinExchange::validLine(line, date, value, err)) {
            if (!err.empty())
				std::cout << err << std::endl;
            continue;
        }

        double rate = 0.0;
        if (!ex.getRate(date, rate)) {
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }

        double result = value * rate;
        std::cout << date << " => " << BitcoinExchange::TrimDec(value)
                  << " = " << BitcoinExchange::TrimDec(result) << std::endl;
    }

    return 0;
}
