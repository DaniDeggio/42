/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:26:37 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/02 14:32:44 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sstream>
#include <cctype>
#include <limits>

struct PM_Pair {
    unsigned int big;
    unsigned int small;
    bool used;
};

// ----- Canonical form -----
PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other) { (void)other; }
PmergeMe& PmergeMe::operator=(const PmergeMe& other) { (void)other; return *this; }
PmergeMe::~PmergeMe() {}

// ----- Parsing: interi positivi entro unsigned int -----
static bool parseUnsigned(const std::string& s, unsigned int& out) {
    if (s.empty()) return false;
    // Solo cifre
    for (size_t i = 0; i < s.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
    }
    // Nessuno zero non-positivo
    unsigned int v = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        unsigned int digit = static_cast<unsigned int>(s[i] - '0');
        // overflow check: v*10 + digit > UINT_MAX
        if (v > (std::numeric_limits<unsigned int>::max() - digit) / 10u) return false;
        v = v * 10u + digit;
    }
    if (v == 0u) return false;
    out = v;
    return true;
}

bool PmergeMe::parseInput(int argc, char** argv, std::vector<unsigned int>& out, std::string& err) {
    out.clear();
    if (argc < 2) { err = "Error"; return false; }
    for (int i = 1; i < argc; ++i) {
        unsigned int v = 0u;
        if (!parseUnsigned(std::string(argv[i]), v)) { err = "Error"; return false; }
        out.push_back(v);
    }
    return true;
}

// ----- Jacobsthal -----
size_t PmergeMe::jacobsthal(size_t n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    size_t j0 = 0, j1 = 1, jn = 0;
    for (size_t i = 2; i <= n; ++i) { jn = j1 + 2 * j0; j0 = j1; j1 = jn; }
    return j1;
}

std::vector<size_t> PmergeMe::buildJacobOrder(size_t m) {
    std::vector<size_t> order;
    if (m <= 1) return order; // indice 1 gestito a parte
    size_t k = 2;
    size_t covered = 1; // abbiamo già “1”
    while (covered < m) {
        size_t j = jacobsthal(k);
        size_t prev = jacobsthal(k - 1);
        if (j > m) j = m;
        for (size_t idx = j; idx > prev; --idx) {
            if (idx >= 2 && idx <= m) order.push_back(idx);
        }
        covered = j;
        ++k;
    }
    // Dedup e completa eventuali indici mancanti 2..m (in coda)
    std::vector<bool> seen(m + 1, false);
    std::vector<size_t> out;
    out.reserve(order.size() + (m > 1 ? m - 1 : 0));
    for (size_t i = 0; i < order.size(); ++i) {
        if (!seen[order[i]]) { seen[order[i]] = true; out.push_back(order[i]); }
    }
    // Aggiunge mancanti in ordine decrescente per coerenza con molti schemi
    for (size_t i = (m >= 2 ? m : 1); i >= 2; --i) {
        if (!seen[i]) out.push_back(i);
        if (i == 2) break;
    }
    return out;
}

// ----- Vector pipeline -----
void PmergeMe::insertWithBoundVector(std::vector<unsigned int>& mainChain, size_t boundPos, unsigned int val) {
    size_t hi = (boundPos > mainChain.size()) ? mainChain.size() : boundPos;
    size_t lo = 0;
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        if (mainChain[mid] < val) lo = mid + 1;
        else hi = mid;
    }
    mainChain.insert(mainChain.begin() + static_cast<std::ptrdiff_t>(lo), val);
}

void PmergeMe::pairAndSortVector(const std::vector<unsigned int>& in,
                                 std::vector<unsigned int>& mainChain,
                                 std::vector<unsigned int>& pendings,
                                 bool& hasOrphan, unsigned int& orphan) {
    std::vector<PM_Pair> pairs;
    pairs.reserve(in.size() / 2);
    hasOrphan = false;
    orphan = 0;

    size_t i = 0;
    for (; i + 1 < in.size(); i += 2) {
        unsigned int a = in[i], b = in[i + 1];
        PM_Pair p;
        if (a >= b) { p.big = a; p.small = b; }
        else        { p.big = b; p.small = a; }
        p.used = false;
        pairs.push_back(p);
    }
    if (i < in.size()) { hasOrphan = true; orphan = in[i]; }

    // estrai i "big" e ordina ricorsivamente
    std::vector<unsigned int> bigs;
    bigs.reserve(pairs.size());
    for (size_t k = 0; k < pairs.size(); ++k) bigs.push_back(pairs[k].big);
    fjSortVector(bigs);

    // mainChain = bigs ordinati
    mainChain = bigs;

    // pendings allineati all’ordine dei bigs
    pendings.clear();
    pendings.reserve(pairs.size());
    for (size_t k = 0; k < bigs.size(); ++k) {
        unsigned int bval = 0u;
        for (size_t t = 0; t < pairs.size(); ++t) {
            if (!pairs[t].used && pairs[t].big == bigs[k]) {
                bval = pairs[t].small;
                pairs[t].used = true;
                break;
            }
        }
        pendings.push_back(bval);
    }
}

void PmergeMe::fjSortVector(std::vector<unsigned int>& data) {
    const size_t n = data.size();
    if (n <= 1) return;

    std::vector<unsigned int> mainChain;
    std::vector<unsigned int> pendings;
    bool hasOrphan = false;
    unsigned int orphan = 0u;

    pairAndSortVector(data, mainChain, pendings, hasOrphan, orphan);
    const size_t m = pendings.size();
    if (m == 0) {
        if (hasOrphan) insertWithBoundVector(mainChain, mainChain.size(), orphan);
        data = mainChain;
        return;
    }

    // posizioni correnti dei big (0..m-1) nella mainChain
    std::vector<size_t> pos(m);
    for (size_t i = 0; i < m; ++i) pos[i] = i;

    // Inserisci il partner del più piccolo big (indice 0) entro [0..pos[0]]
    insertWithBoundVector(mainChain, pos[0], pendings[0]);
    for (size_t j = 0; j < m; ++j) pos[j] += 1;

    // Inserimento restante in ordine Jacobsthal (indici 1..m-1 => 2..m 1-based)
    std::vector<size_t> order = buildJacobOrder(m);
    for (size_t u = 0; u < order.size(); ++u) {
        size_t idx1 = order[u];      // 1-based
        size_t idx  = idx1 - 1;      // 0-based
        if (idx >= m) continue;
        insertWithBoundVector(mainChain, pos[idx], pendings[idx]);
        for (size_t j = idx; j < m; ++j) pos[j] += 1;
    }

    if (hasOrphan) insertWithBoundVector(mainChain, mainChain.size(), orphan);
    data = mainChain;
}

// ----- Deque pipeline -----
void PmergeMe::insertWithBoundDeque(std::deque<unsigned int>& mainChain, size_t boundPos, unsigned int val) {
    size_t hi = (boundPos > mainChain.size()) ? mainChain.size() : boundPos;
    size_t lo = 0;
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        if (mainChain[mid] < val) lo = mid + 1;
        else hi = mid;
    }
    mainChain.insert(mainChain.begin() + static_cast<std::ptrdiff_t>(lo), val);
}

void PmergeMe::pairAndSortDeque(const std::deque<unsigned int>& in,
                                std::deque<unsigned int>& mainChain,
                                std::deque<unsigned int>& pendings,
                                bool& hasOrphan, unsigned int& orphan) {
    std::vector<PM_Pair> pairs; // temporaneo
    pairs.reserve(in.size() / 2);
    hasOrphan = false;
    orphan = 0;

    size_t i = 0;
    for (; i + 1 < in.size(); i += 2) {
        unsigned int a = in[i], b = in[i + 1];
        PM_Pair p;
        if (a >= b) { p.big = a; p.small = b; }
        else        { p.big = b; p.small = a; }
        p.used = false;
        pairs.push_back(p);
    }
    if (i < in.size()) { hasOrphan = true; orphan = in[i]; }

    // estrai e ordina ricorsivamente i big
    std::deque<unsigned int> bigs;
    for (size_t k = 0; k < pairs.size(); ++k) bigs.push_back(pairs[k].big);
    fjSortDeque(bigs);

    // mainChain = bigs
    mainChain.clear();
    for (size_t k = 0; k < bigs.size(); ++k) mainChain.push_back(bigs[k]);

    // pendings allineati
    pendings.clear();
    for (size_t k = 0; k < bigs.size(); ++k) {
        unsigned int bval = 0u;
        for (size_t t = 0; t < pairs.size(); ++t) {
            if (!pairs[t].used && pairs[t].big == bigs[k]) {
                bval = pairs[t].small;
                pairs[t].used = true;
                break;
            }
        }
        pendings.push_back(bval);
    }
}

void PmergeMe::fjSortDeque(std::deque<unsigned int>& data) {
    const size_t n = data.size();
    if (n <= 1) return;

    std::deque<unsigned int> mainChain;
    std::deque<unsigned int> pendings;
    bool hasOrphan = false;
    unsigned int orphan = 0u;

    pairAndSortDeque(data, mainChain, pendings, hasOrphan, orphan);
    const size_t m = pendings.size();
    if (m == 0) {
        if (hasOrphan) insertWithBoundDeque(mainChain, mainChain.size(), orphan);
        data = mainChain;
        return;
    }

    std::vector<size_t> pos(m);
    for (size_t i = 0; i < m; ++i) pos[i] = i;

    insertWithBoundDeque(mainChain, pos[0], pendings[0]);
    for (size_t j = 0; j < m; ++j) pos[j] += 1;

    std::vector<size_t> order = buildJacobOrder(m);
    for (size_t u = 0; u < order.size(); ++u) {
        size_t idx = order[u] - 1;
        if (idx >= m) continue;
        insertWithBoundDeque(mainChain, pos[idx], pendings[idx]);
        for (size_t j = idx; j < m; ++j) pos[j] += 1;
    }

    if (hasOrphan) insertWithBoundDeque(mainChain, mainChain.size(), orphan);
    data = mainChain;
}

void PmergeMe::sortVector(std::vector<unsigned int>& data) { fjSortVector(data); }
void PmergeMe::sortDeque(std::deque<unsigned int>& data) { fjSortDeque(data); }
