//
// Created by krutna on 01.10.18.
//

#ifndef TURING_MACHINE_TURING_MACHINE_HPP
#define TURING_MACHINE_TURING_MACHINE_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

class TuringMachine {
public:
    std::stringstream toFile;

    TuringMachine(std::vector<char>* matrix, std::vector<char>* tape, int* dimension);
    void init(bool toClear);
    void execute();
private:
    int current = 1;
    int step = 0;
    bool isEnded = false;
    int command = 1;

    std::vector<char>* preMatrix;
    std::vector<char>* preTape;
    int* preDimension;

    int dimension;
    std::vector<char> matrix;
    std::vector<char> tape;

    void toEnd();

    void executeStep();

    void printTape(bool toStream);
};


#endif //TURING_MACHINE_TURING_MACHINE_HPP
