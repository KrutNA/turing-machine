//
// Created by krutna on 01.10.18.
//

#ifndef TURING_MACHINE_INPUT_VALIDATOR_HPP
#define TURING_MACHINE_INPUT_VALIDATOR_HPP

#include <iostream>
#include <vector>
#include <regex>
#include <fstream>

class InputValidator {
public:
    bool validateMatrix(std::vector<char> *matrix, std::vector<char> *tape,
                        char* args[], int* dimension,
                        bool isMatrixInFile, bool isTapeInFile);
private:
    std::regex regexes[6] = {
            std::regex("([\t\\s]*[sS0-9][0-9][rRlLcC])+[\\s\t]*"),
            std::regex("[sS0-9][0-9][rRlLcC]"),
            std::regex("([\t\\s]*[sS0-9]+[\t\\s]*)"),
            std::regex("[sS0-9]+"),
            std::regex("[\t\\s]*[1-9][\\s\t]*"),
            std::regex("[1-9]")
    };

    bool checkMatrixLine(std::vector<char>* vector, std::string* value, int dimension, int iterator);

    bool checkTapeLine(std::vector<char>* vector, std::string* value);

    bool readMatrixFromFile(std::vector<char> *vector, char* fileName, int* dimension);

    bool readMatrixFromStream(std::vector<char> *vector, int* dimension);

    bool readTapeFromFile(std::vector<char> *vector, char* fileName);

    bool readTapeFromStream(std::vector<char> *vector);
};


#endif //TURING_MACHINE_INPUT_VALIDATOR_HPP
