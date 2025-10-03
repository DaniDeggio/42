/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:37:49 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/03 05:43:20 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <cctype>

RPN::RPN() {}
RPN::RPN(const RPN& other) { 
	(void)other;
}

RPN& RPN::operator=(const RPN& other) {
	(void)other;
	return *this;
}

RPN::~RPN() {}


static bool add_op(long left, long right, long& out) {
    out = left + right;
    return true;
}

static bool sub_op(long left, long right, long& out) {
    out = left - right;
    return true;
}

static bool mul_op(long left, long right, long& out) {
    out = left * right;
    return true;
}

static bool div_op(long left, long right, long& out) {
    if (right == 0)
        return false;
    out = left / right;
    return true;
}

bool RPN::applyOp(long left, long right, char op, long& out) {
	if (op == '+') {
		return add_op(left, right, out);
    } else if (op == '-') {
		return sub_op(left, right, out);
    } else if (op == '*') {
		return mul_op(left, right, out);
    } else if (op == '/') {
		return div_op(left, right, out);
    }
    return false;
}

bool RPN::isOp(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

bool RPN::evaluate(const std::string& expr, long& out) const {
    std::istringstream iss(expr.c_str());
    std::stack<long> st;
    std::string tok;

    while (iss >> tok) {
        if (tok.size() == 1 && std::isdigit(static_cast<unsigned char>(tok[0]))) {
            long v = tok[0] - '0';
            st.push(v);
        } else if (tok.size() == 1 && isOp(tok[0])) {
            if (st.size() < 2)
				return false;

            long a = st.top(); st.pop();
            long b = st.top(); st.pop();
            long r;
	
            if (!applyOp(b, a, tok[0], r))
				return false;
            st.push(r);
        } else {
            return false;
        }
    }

    if (st.size() != 1)
		return false;
    out = st.top();
    return true;
}
