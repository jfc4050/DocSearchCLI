//
// Created by Justin on 9/27/17.
//

#ifndef DOCUMENTSEARCHER_TXTPROCESSOR_H
#define DOCUMENTSEARCHER_TXTPROCESSOR_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>

class TxtProcessor {
    std::string filePath;
    std::string delimiter;
public:
    TxtProcessor(std::string fileIn);

    std::vector<std::string> processTxt(bool phraseSearch);
};

#endif //DOCUMENTSEARCHER_TXTPROCESSOR_H
