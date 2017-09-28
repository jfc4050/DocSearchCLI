//
// Created by Justin on 9/27/17.
//

#include "TxtProcessor.h"

TxtProcessor::TxtProcessor(std::string fileIn){
    filePath = std::move(fileIn);
}

std::vector<std::string> TxtProcessor::processTxt(bool phraseSearch) {
    std::ifstream inFile(filePath);
    std::string line{};

//    if (phraseSearch) {
//        std::vector<std::string> stringVect;
//        while (getline(inFile,line)) {
//            std::vector<std::string> tempVector;
//            boost::algorithm::split(tempVector, line, boost::is_any_of("\t,\n|!? .-'\" ;()"));
//            stringVect.insert(stringVect.end(), tempVector.begin(), tempVector.end());
//            std::copy(tempVector.begin(), tempVector.end(), std::inserter(tempVector, tempVector.end()));
//        }
//        inFile.close();
//        return stringVect;
//    }

//    else {
        //if not phraseSearch
        std::set<std::string> stringSet{};
        while (getline(inFile,line)) {
            std::set<std::string> tempSet;
            boost::algorithm::split(tempSet, line, boost::is_any_of("\t,\n|!? .-'\" ;()"));
            stringSet.insert(tempSet.begin(), tempSet.end());
        }
        inFile.close();
        std::vector<std::string> output(stringSet.begin(), stringSet.end());
        return output;
//    }
}