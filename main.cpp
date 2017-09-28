#include <iostream>
#include <ctime>
#include "TxtSearcher.h"
#include "TxtProcessor.h"

void printPairs(std::vector<std::pair<std::string,int>> vecIn) {
    int pairs = 0;
    for (const auto& pair : vecIn) {
        pairs++;
        std::cout << "LevenshteinDistance[" << pair.first << "] = " << pair.second << std::endl;
    }
    std::cout << pairs << " pairs" << std::endl;
}

std::vector< std::pair<std::string, int> > mapToVector(std::map<std::string, int>& mapIn) {

    std::vector< std::pair<std::string,int> > vectorOut(mapIn.size());

    int i = 0;
    for (const auto& pair : mapIn) {
        vectorOut[i] = pair;
        i++;
    }
    return vectorOut;
}

void quickSortPairs(std::vector<std::pair<std::string,int>>& final,
                    std::vector<std::pair<std::string,int>>::iterator left,
                    std::vector<std::pair<std::string,int>>::iterator right)
{
    if (right != left) {

        unsigned long randInt = rand() % std::distance(left, right);
        auto pivot = left + randInt;
        std::iter_swap(left, pivot);
        pivot = left;
        auto boundary = left+1;

        //partition around pivot;
        for (auto temp = boundary ; temp != right ; ++temp) {
            if (temp->second < pivot->second) {
                std::iter_swap(temp, boundary);
                boundary++;
            }
        }

        //put pivot element in rightful position
        boundary--;
        std::iter_swap(pivot, boundary);

        quickSortPairs(final, left, boundary);
        quickSortPairs(final, ++boundary, right);
    }
}


int main() {

    int start_s = clock();
    TxtProcessor* txt = new TxtProcessor("/Users/justin/Desktop/sorcerersStone.txt");
    std::vector<std::string> output = txt->processTxt(false);

    TxtSearcher* search = new TxtSearcher(output);
    delete txt;

    std::vector<std::pair<std::string,int>> final = search->levenshteinFromVector("justin");
    delete search;
    quickSortPairs(final, final.begin(), final.end());
    int stop_s = clock();
    std::cout << "finished in: " << (stop_s-start_s)/double(CLOCKS_PER_SEC) << " seconds" << std::endl;
    printPairs(final);

    return 0;
}