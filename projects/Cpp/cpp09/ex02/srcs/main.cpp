/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 23:38:13 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/02 14:33:20 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/PmergeMe.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <deque>

static void printSeq(const std::vector<unsigned int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) std::cout << ' ';
        std::cout << v[i];
    }
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    std::vector<unsigned int> input;
    std::string err;
    if (!PmergeMe::parseInput(argc, argv, input, err)) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    std::cout << "Before: ";
    printSeq(input);

    std::vector<unsigned int> v = input;
    std::deque<unsigned int> d(input.begin(), input.end());

    std::clock_t c0 = std::clock();
    PmergeMe::sortVector(v);
    std::clock_t c1 = std::clock();

    std::clock_t c2 = std::clock();
    PmergeMe::sortDeque(d);
    std::clock_t c3 = std::clock();

    std::cout << "After: ";
    printSeq(v);

    double dt_vec_us = 1e6 * double(c1 - c0) / double(CLOCKS_PER_SEC);
    double dt_deq_us = 1e6 * double(c3 - c2) / double(CLOCKS_PER_SEC);

    std::cout << "Time to process a range of " << v.size()
              << " elements with std::vector : "
              << std::fixed << std::setprecision(5) << dt_vec_us << " us" << std::endl;

    std::cout << "Time to process a range of " << d.size()
              << " elements with std::deque  : "
              << std::fixed << std::setprecision(5) << dt_deq_us << " us" << std::endl;

    return 0;
}
