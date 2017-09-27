//
// Created by Justin on 9/27/17.
//

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>
#include <cassert>
#include <random>
#include <algorithm>
#include <utility>

#ifndef DOCUMENTSEARCHER_TXTSEARCHER_H
#define DOCUMENTSEARCHER_TXTSEARCHER_H

class TxtSearcher {
private:
    std::ifstream inFile;
public:
    // NAIVE ALGORITHM
    int readAndCountNaive(const std::string& filePath, const std::string& query);

    // Rabin Fingerprint Generator
    int rabinFingerprint(const std::string& inputStr, const int base=101);

    // RABIN-KARP ALGORITHM
    int readAndCountRK(const std::string& filePath, const std::string& query);

    // LEVENSHTEIN STRING COMPARISON
    int levenshteinDistance(const std::string& str, const std::string& target, bool testing=false);

    // Levenshtein Comparison with each word
    std::map<std::string, int> levenshteinEachWord(const std::string& filePath, const std::string& query, bool testing=false);

    // Levenshtein Comparison with phrases
    std::map<std::string, int> TxtSearcher::levenshteinPhrases(const std::string& filePath, const std::string& query);

};

#endif //DOCUMENTSEARCHER_TXTSEARCHER_H
