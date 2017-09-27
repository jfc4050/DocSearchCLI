//
// Created by Justin on 9/27/17.
//

#include "TxtSearcher.h"

// NAIVE ALGORITHM
int TxtSearcher::readAndCountNaive(const std::string& filePath, const std::string& query) {
    //Generate Vector of words in query
    std::stringstream sStr(query);
    std::string wordInQuery;
    std::vector<std::string> wordsInQuery;
    while (sStr >> wordInQuery)
        wordsInQuery.push_back(wordInQuery);
    inFile.open(filePath);
    int count = 0;
    std::string currentWord;
    while (inFile >> currentWord) {
        bool match = false;
        int i = 0;
        if (currentWord == wordsInQuery[0]) {
            match = true;
            i++;
        }
        while (match and i < wordsInQuery.size()) {
            inFile >> currentWord;
            if (currentWord != wordsInQuery[i]) {
                match = false;
                break;
            }
            i++;
        }
        if (match) count++;
    }
    inFile.close();
    return count;
}

// Rabin Fingerprint Generator
int TxtSearcher::rabinFingerprint(const std::string& inputStr, const int base) {
    int hash = 0;
    int i = 0;
    for (char currChar : inputStr) {
        hash += currChar*(base^i);
        i++;
    }
    return hash;
}


// RABIN-KARP ALGORITHM
int TxtSearcher::readAndCountRK(const std::string& filePath, const std::string& query) {
    // Generate vector of characters in file
    inFile.open(filePath);
    std::vector<char> fileChars;
    char charIn;
    while (inFile >> std::noskipws >> charIn)
        fileChars.emplace_back(charIn);
    inFile.close();

    // Iterate through vector of characters in file, looking for target hash value
    int target = rabinFingerprint(query);
    int count = 0;
    for (auto iter = fileChars.begin() ; iter < fileChars.end() ; ++iter) {
        if (*iter == query.at(0)) {
            std::string candidateStr(iter, iter+query.size());
            if (rabinFingerprint(candidateStr) == target) {
                count++;
            }
        }
    }
    return count;
}

// LEVENSHTEIN STRING COMPARISON
int TxtSearcher::levenshteinDistance(const std::string& str, const std::string& target, bool testing) {
    int rows = (int) str.size() + 1;        //set array dimensions and declare
    int cols = (int) target.size() + 1;
    int dist[rows][cols];

    // populate string comparisons with empty string
    for (int i = 0 ; i < rows ; ++i)
        dist[i][0] = i;
    for (int j = 0 ; j < cols ; ++j)
        dist[0][j] = j;

    for (int row = 1 ; row < rows ; ++row) {
        for (int col = 1 ; col < cols ; ++col) {
            int cost;
            (str[row-1] == target[col-1]) ? cost = 0 : cost = 1;    // determine if operation is necessary

            dist[row][col] = std::min( { dist[row-1][col] + 1,           // deletion
                                         dist[row][col-1] + 1,           // insertion
                                         dist[row-1][col-1] + cost } );   // substitution

            if (testing)
                assert(dist[row][col] <= rows and dist[row][col] <= cols);
        }
    }
    return dist[rows-1][cols-1];        //levenshtein distance is contents of lower right member
}

// Levenshtein Comparison with each word
std::map<std::string, int> TxtSearcher::levenshteinEachWord(const std::string& filePath, const std::string& query, bool testing) {
    if (testing) {
        std::cout << query << std::endl;
    }

    inFile.open(filePath);
    std::string curWord;
    std::map<std::string, int> comparisons;

    int dist;
    while(inFile >> curWord) {
        dist = levenshteinDistance(curWord, query);

        if (testing) {
            std::cout << "Current Comparison: " << curWord << "/" << query << " - " << "Distance: " << dist << std::endl;
            std::cout << "Count in Dictionary: " << comparisons.count(curWord) << std::endl
                      << "\n";
        }

        if (comparisons.find(curWord) != comparisons.end()) { ; }
        else { comparisons[curWord] = dist; }

    }
    inFile.close();

    //returns map of key value pairs (each word, distance)
    return comparisons;
}
