/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:59:50 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/02 14:13:28 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/RPN.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    RPN calc;
    long result = 0;
    if (!calc.evaluate(std::string(argv[1]), result)) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    std::cout << result << std::endl;
    return 0;
}
