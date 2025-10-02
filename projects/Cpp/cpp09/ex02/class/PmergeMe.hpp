/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:37:49 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/02 14:33:30 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe {
public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    // Parsing argv -> vector<unsigned int> (solo interi positivi)
    static bool parseInput(int argc, char** argv, std::vector<unsigned int>& out, std::string& err);

    // Ordinamenti specifici per contenitore
    static void sortVector(std::vector<unsigned int>& data);
    static void sortDeque(std::deque<unsigned int>& data);

private:
    // Jacobsthal helpers
    static size_t jacobsthal(size_t n);
    static std::vector<size_t> buildJacobOrder(size_t m);

    // Vector pipeline
    static void fjSortVector(std::vector<unsigned int>& data);
    static void insertWithBoundVector(std::vector<unsigned int>& mainChain, size_t boundPos, unsigned int val);
    static void pairAndSortVector(const std::vector<unsigned int>& in,
                                  std::vector<unsigned int>& mainChain,
                                  std::vector<unsigned int>& pendings,
                                  bool& hasOrphan, unsigned int& orphan);

    // Deque pipeline
    static void fjSortDeque(std::deque<unsigned int>& data);
    static void insertWithBoundDeque(std::deque<unsigned int>& mainChain, size_t boundPos, unsigned int val);
    static void pairAndSortDeque(const std::deque<unsigned int>& in,
                                 std::deque<unsigned int>& mainChain,
                                 std::deque<unsigned int>& pendings,
                                 bool& hasOrphan, unsigned int& orphan);
};

#endif