/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:37:49 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/02 14:12:49 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <cctype>

RPN::RPN() {}
RPN::RPN(const RPN& other) { (void)other; }
RPN& RPN::operator=(const RPN& other) { (void)other; return *this; }
RPN::~RPN() {}

bool RPN::isOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool RPN::applyOp(long left, long right, char op, long& out) {
    switch (op) {
        case '+': out = left + right; return true;
        case '-': out = left - right; return true;
        case '*': out = left * right; return true;
        case '/':
            if (right == 0) return false; // divisione per zero -> errore
            out = left / right; // divisione intera, troncamento verso zero
            return true;
        default: return false;
    }
}

bool RPN::evaluate(const std::string& expr, long& out) const {
    std::istringstream iss(expr.c_str());
    std::stack<long> st;
    std::string tok;

    while (iss >> tok) {
        if (tok.size() == 1 && std::isdigit(static_cast<unsigned char>(tok[0]))) {
            long v = tok[0] - '0'; // numeri < 10 come da soggetto
            st.push(v);
        } else if (tok.size() == 1 && isOp(tok[0])) {
            if (st.size() < 2) return false;
            long a = st.top(); st.pop(); // right operand
            long b = st.top(); st.pop(); // left operand
            long r;
            if (!applyOp(b, a, tok[0], r)) return false;
            st.push(r);
        } else {
            // token non valido (p.es. parentesi, multi-digit, decimali, simboli)
            return false;
        }
    }

    if (st.size() != 1) return false;
    out = st.top();
    return true;
}
