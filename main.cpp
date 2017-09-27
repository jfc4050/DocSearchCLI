#include <iostream>
#include "TxtSearcher.h"

void printMap(std::map<std::string,int> mapIn) {
    for (const auto& pair : mapIn) {
        std::cout << "LevenshteinDistance[" << pair.first << "] = " << pair.second << std::endl;
    }
}
void printVector(std::vector<std::pair<std::string,int>> vecIn) {
    for (const auto& pair : vecIn) {
        std::cout << "LevenshteinDistance[" << pair.first << "] = " << pair.second << std::endl;
    }
}

std::vector< std::pair<std::string, int> > mapToVector(std::map<std::string, int>& mapIn) {

    std::vector< std::pair<std::string,int> > vectorOut;

    for (const auto& pair : mapIn) {
        vectorOut.emplace_back(pair);
    }
    return vectorOut;
}


std::vector<std::pair<std::string, int>> quickSortDictionary(std::vector<std::pair<std::string,int>>& unsorted,
                                                             std::vector<std::pair<std::string,int>>::iterator left,
                                                             std::vector<std::pair<std::string,int>>::iterator right) {

    if (right != left) {
        //set pivot and boundary
        auto pivot = left;
        auto boundary = left+1;

        //partition around pivot;
        for (auto temp = boundary ; temp != right ; ++temp) {
            if (temp->second < pivot->second) {
                std::iter_swap(temp, boundary);
                boundary++;
            }
        }
        boundary--;
        std::iter_swap(pivot, boundary);

        quickSortDictionary(unsorted, left, boundary);
        quickSortDictionary(unsorted, ++boundary, right);
    }
    return unsorted;
}


int main() {
    TxtSearcher* txt = new TxtSearcher;
    std::string path = "/Users/justin/Desktop/sorcerersStone.txt";
    std::map<std::string, int> output = txt->levenshteinEachWord(path, "justin");
    delete txt;

    std::vector<std::pair<std::string,int>> vectorResults = mapToVector(output);

//    std::cout << "printing (unsorted) vector " << std::endl;
//    printVector(vectorResults);
//    std::cout << "\n";

    std::vector<std::pair<std::string,int> > sorted = quickSortDictionary(vectorResults, vectorResults.begin(), vectorResults.end());

    std::cout << "printing sorted vector:" << std::endl;
    printVector(sorted);




    return 0;
}