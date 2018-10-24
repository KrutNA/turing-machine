//
// Created by krutna on 01.10.18.
//

#include "input-validator.hpp"

bool InputValidator::validateMatrix(
        std::vector<char>* matrix, std::vector<char>* tape,
        char* args[], int* dimension,
        bool isMatrixInFile = false, bool isTapeInFile = false) {
    bool result = false;

    if (isMatrixInFile) {
        if (!readMatrixFromFile(matrix, args[0], dimension)) {
            goto returnLabel;
        }
    } else {
        if (!readMatrixFromStream(matrix, dimension)) {
            goto returnLabel;
        }
    }

    if (isTapeInFile) {
        if (!readTapeFromFile(tape, args[1])) {
            goto returnLabel;
        }
    } else {
        if (!readTapeFromStream(tape)) {
            goto returnLabel;
        }
    }
    for (int i = 0; i < (*matrix).size()/3; i++) {

        if ((int)(*matrix)[i*3] - 48 > (*dimension) ||
            (tolower((*matrix)[i*3 + 1]) != 's' && (int)(*matrix)[i*3 + 1] - 48 > (*dimension) - 1)) {

            std::cout << "Error on line " << i/(*dimension) + 1 << std::endl
                      << "With argument " << i/(*dimension + 1) + 1 << std::endl;
            goto returnLabel;

        }
    }

    result = true;
    returnLabel:
    return result;
}

bool InputValidator::checkMatrixLine(std::vector<char>* vector, std::string* value, int dimension, int iterator) {
    auto arrStart = std::sregex_iterator((*value).begin(), (*value).end(), regexes[1]);
    auto arrEnd = std::sregex_iterator();
    if (!(std::regex_match((*value), regexes[0]) && (dimension) + 1 == std::distance(arrStart, arrEnd))) {
        std::cout << "Error on reading matrix line " << iterator + 1 << std::endl;
        return false;
    }
    for (auto j = arrStart; j != arrEnd; ++j) {
        for (int k = 0; k < 3; ++k) {
            vector->push_back((*j).str()[k]);
        }
    }
    return true;
}

bool InputValidator::checkTapeLine(std::vector<char> *vector, std::string* value) {
    if (!std::regex_match((*value), regexes[2])) {
        std::cout << "Line is not match the tape!" << std::endl;
        return false;
    }
    *value = (*std::sregex_iterator((*value).begin(), (*value).end(), regexes[3])).str();
    for (char i : (*value))
        vector->push_back(i);
    return  true;
}

bool InputValidator::readMatrixFromFile(
        std::vector<char>* vector, char* fileName, int* dimension) {
    std::cout << "Reading matrix from file..." << std::endl;
    bool result = false;
    std::string value;
    std::ifstream file (fileName);
    if (!file.is_open()) {
        std::cout << "Cant open file " << fileName << " for reading!" << std::endl;
        goto returnLabel;
    }
    if (!getline(file, value)) {
        std::cout << "Can't read line: 1" << std::endl;
        goto returnLabel;
    }
    if (!std::regex_match(value, regexes[4])) {
        std::cout << "Dimension of matrix is invalid!" << std::endl;
        goto returnLabel;
    }
    (*dimension) = std::stoi((*std::sregex_iterator(value.begin(), value.end(), regexes[5]))[0]);

    for (int i = 0; i < (*dimension); ++i) {
        if (!getline(file, value)) {
            std::cout << "Can't read line: " << i+2 << std::endl;
            goto returnLabel;
        }
        if (!checkMatrixLine(vector, &value, *dimension, i))
            goto returnLabel;
    }
    while (getline(file, value)) {
        if (!value.empty()) {
            std::cout << "Too much lines in file!" << std::endl;
            goto returnLabel;
        }
    }

    std::cout << "Dimension: " << *dimension << std::endl
              << "Matrix:" << std::endl;
    for (int i = 0; i < (*dimension); ++i) {
        for (int j = 0; j < (*dimension) + 1; ++j) {
            std::cout << (*vector)[(i*((*dimension))+j)*3] << (*vector)[(i*((*dimension))+j)*3+1] << (*vector)[(i*((*dimension))+j)*3+2] << " ";
        }
        std::cout << std::endl;
    }
    result = true;
    returnLabel:
    file.close();
    return result;
}

bool InputValidator::readMatrixFromStream(
        std::vector<char>* vector, int* dimension) {
    std::string value;
    bool result = false;

    std::cout << "Input matrix:" << std::endl;
    for (int i = 0; i < (*dimension); ++i) {
        std::getline(std::cin, value);
        if (!checkMatrixLine(vector, &value, *dimension, i))
            goto returnLabel;
    }

    result = true;
    returnLabel:
    return result;
}

bool InputValidator::readTapeFromFile(
        std::vector<char>* vector, char* fileName) {
    std::string value;
    bool result = false;
    std::ifstream file(fileName);
    if (!getline(file, value) || value.empty()) {
        std::cout << "Can't read tape from file!" << std::endl;
        goto returnLabel;
    }
    if (!checkTapeLine(vector, &value))
        goto returnLabel;
    while (getline(file, value)) {
        if (!value.empty()) {
            std::cout << "Too much lines in file!" << std::endl;
            goto returnLabel;
        }
    }

    result = true;
    returnLabel:
    file.close();
    return result;
}

bool InputValidator::readTapeFromStream(
        std::vector<char>* vector) {
    std::string value;
    bool result = false;
    std::cout << "Input tape:" << std::endl;
    std::getline(std::cin, value);
    if (!checkTapeLine(vector, &value))
        goto returnLabel;

    result = true;
    returnLabel:
    return result;
}