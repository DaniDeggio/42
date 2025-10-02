/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:37:49 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/02 13:57:07 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>


BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
: _rates(other._rates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        _rates = other._rates;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadCSV(const std::string& path) {
    std::ifstream in(path.c_str());
    if (!in) {
        // Silenzioso secondo molte soluzioni; il main può decidere come reagire
        return;
    }
    std::string line;
    // Possibile header "date,exchange_rate"
    if (std::getline(in, line)) {
        // Se la riga inizia con "date" la si considera header e si prosegue
        std::string head = trim(line);
        if (head.size() >= 4) {
            std::string prefix = head.substr(0, 4);
            for (size_t i = 0; i < prefix.size(); ++i) prefix[i] = static_cast<char>(std::tolower(prefix[i]));
            if (prefix != "date") {
                // la prima riga potrebbe essere già dato; processarla
                std::string d, p;
                splitOnce(line, ',', d, p);
                d = trim(d);
                p = trim(p);
                double rate;
                if (isValidDate(d) && parseDouble(p, rate)) {
                    _rates[d] = rate;
                }
            }
        }
    }
    // Resto del file
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::string d, p;
        splitOnce(line, ',', d, p);
        d = trim(d);
        p = trim(p);
        double rate;
        if (isValidDate(d) && parseDouble(p, rate)) {
            _rates[d] = rate;
        }
        // Righe invalide del DB sono ignorate
    }
}

bool BitcoinExchange::getRate(const std::string& date, double& rate) const {
    if (_rates.empty()) return false;
    std::map<std::string, double>::const_iterator it = _rates.lower_bound(date);
    if (it != _rates.end() && it->first == date) {
        rate = it->second;
        return true;
    }
    if (it == _rates.begin()) {
        // Tutti gli elementi sono >= date, quindi non esiste precedente
        return false;
    }
    // L'elemento precedente a it è la data immediatamente minore
    --it;
    rate = it->second;
    return true;
}

bool BitcoinExchange::validLine(const std::string& line,
                                        std::string& date,
                                        double& value,
                                        std::string& errorMsg) {
    date.clear();
    value = 0.0;
    errorMsg.clear();

    // salta header "date | value"
    std::string t = trim(line);
    if (t.size() >= 4) {
        std::string prefix = t.substr(0, 4);
        for (size_t i = 0; i < prefix.size(); ++i) prefix[i] = static_cast<char>(std::tolower(prefix[i]));
        if (prefix == "date") return false; // nessun output per l'header
    }

    std::string valueStr;
    if (!trimSplit(line, date, valueStr)) {
        errorMsg = std::string("Error: bad input => ") + t;
        return false;
    }
    if (!isValidDate(date)) {
        errorMsg = std::string("Error: bad input => ") + t;
        return false;
    }
    if (!parseDouble(valueStr, value)) {
        errorMsg = std::string("Error: bad input => ") + t;
        return false;
    }
    if (value < 0.0) {
        errorMsg = "Error: not a positive number.";
        return false;
    }
    if (value > 1000.0) {
        errorMsg = "Error: too large a number.";
        return false;
    }
    return true;
}

// --------- utility private ---------

bool BitcoinExchange::isLeap(int y) {
    // gregoriano: divisibile per 400, o divisibile per 4 ma non per 100
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    return (y % 4 == 0);
}

bool BitcoinExchange::isValidDate(const std::string& s) {
    // formato "YYYY-MM-DD"
    if (s.size() != 10) return false;
    if (s[4] != '-' || s[7] != '-') return false;
    for (size_t i = 0; i < s.size(); ++i) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
    }
    int y = std::atoi(s.substr(0,4).c_str());
    int m = std::atoi(s.substr(5,2).c_str());
    int d = std::atoi(s.substr(8,2).c_str());
    if (y <= 0) return false;
    if (m < 1 || m > 12) return false;
    int mdays[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int days = mdays[m-1];
    if (m == 2 && isLeap(y)) days = 29;
    if (d < 1 || d > days) return false;
    return true;
}

bool BitcoinExchange::parseDouble(const std::string& s, double& out) {
    std::istringstream iss(s);
    iss.setf(std::ios::fmtflags(0), std::ios::floatfield); // default
    double v;
    iss >> v;
    if (!iss || iss.fail()) return false;
    // assicurarsi che non restino caratteri non-spazio
    char c;
    if (iss >> c) return false;
    out = v;
    return true;
}

bool BitcoinExchange::trimSplit(const std::string& line, std::string& date, std::string& valueStr) {
    // formato "date | value" con spazi opzionali attorno a '|'
    std::string t = trim(line);
    // trova il separatore '|'
    std::string left, right;
    splitOnce(t, '|', left, right);
    if (right.empty()) return false;
    date = trim(left);
    valueStr = trim(right);
    // Il soggetto mostra esplicitamente spazi attorno alla barra verticale, ma si accetta anche senza
    return !date.empty() && !valueStr.empty();
}

std::string BitcoinExchange::ltrim(const std::string& s) {
    size_t i = 0;
    while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
    return s.substr(i);
}

std::string BitcoinExchange::rtrim(const std::string& s) {
    if (s.empty()) return s;
    size_t i = s.size();
    while (i > 0 && std::isspace(static_cast<unsigned char>(s[i-1]))) --i;
    return s.substr(0, i);
}

std::string BitcoinExchange::trim(const std::string& s) {
    return rtrim(ltrim(s));
}

void BitcoinExchange::splitOnce(const std::string& s, char sep, std::string& left, std::string& right) {
    size_t pos = s.find(sep);
    if (pos == std::string::npos) { left = s; right.clear(); return; }
    left = s.substr(0, pos);
    right = s.substr(pos + 1);
}

std::string BitcoinExchange::TrimDec(double v) {
    std::ostringstream oss;
    oss << std::setprecision(10) << v;
    std::string out = oss.str();
    // rimuove zeri finali e punto se inutile
    if (out.find('.') != std::string::npos) {
        while (!out.empty() && out[out.size()-1] == '0') out.erase(out.size()-1);
        if (!out.empty() && out[out.size()-1] == '.') out.erase(out.size()-1);
    }
    return out;
}
