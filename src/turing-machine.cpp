//
// Created by krutna on 01.10.18.
//

#include "turing-machine.hpp"

TuringMachine::TuringMachine(const std::vector<char>&& matrix, const std::vector<char>&& tape, int dimension)
    : matrix(matrix)
    , tape(tape)
    , dimension(dimension) {}

void TuringMachine::execute() {
    std::string str;
    std::cout << "'exit' - to stop executing turing machine" << std::endl
              << "'step' - to execute step" << std::endl
              << "'end'  - to execute to end" << std::endl;
    printTape(true);
    std::cin >> str;
    while (str != "exit" && !str.empty()) {
        if (str == "step") {
            executeStep();
        } else if (str == "end") {
            toEnd();
        }
        std::cout << "> ";
        std::cin >> str;
    }
    std::cout << "Save to file? y/n: ";
    char ch;
    std::string fileName;
    std::ofstream file;
    std::cin >> ch;
    if (tolower(ch) == 'y') {
        std::cin >> fileName;
        file.open(fileName, std::ofstream::out);
        file << toFile.rdbuf();
        file.close();
    }
}

void TuringMachine::toEnd() {
    if (isEnded || step > 1000) {
        std::cout << "Machine is already finished" << std::endl;
        printTape(false);
    }
    while (!isEnded && step <= 1000) {
        executeStep();
    }
}

void TuringMachine::executeStep() {
    if (!isEnded && step <= 1000) {

        int newCommand = matrix[((command-1)*(dimension+1) +
                                tolower(tape[current] == 's' ? 0 : (int)(tape[current]) - 47)) * 3] - 48;
        char newChar   = matrix[((command-1)*(dimension+1) +
                                tolower(tape[current] == 's' ? 0 : (int)(tape[current]) - 47)) * 3 + 1];
        char stepType  = matrix[((command-1)*(dimension+1) +
                                tolower(tape[current] == 's' ? 0 : (int)(tape[current]) - 47)) * 3 + 2];

        tape[current] = newChar;
        command = newCommand;

        current = tolower(stepType) == 'r' ? current + 1 :
                  tolower(stepType) == 'l' ? current - 1 : current;
        if (current == tape.size())
            tape.push_back(newChar);
        else if (current == -1) {
            tape.insert(tape.begin(), newChar);
            current++;
        }

        step++;
        printTape(true);
        if (command == 0) {
            isEnded = true;
            std::cout << "Machine finished" << std::endl;
        }
    } else {
        std::cout << "Machine is already finished" << std::endl;
        printTape(false);
    }
}

void TuringMachine::printTape(bool toStream = true) {
    int i = 0;

    if (toStream)
        toFile << step << ":\t";
    std::cout << step << ":\t";

    while (i != current) {
        if (toStream)
            toFile << tape[i];
        std::cout << tape[i++];
    }

    if (toStream)
        toFile << ">" << tape[current] << "<";
    std::cout << ">" << tape[current] << "<";

    while (i != tape.size()) {
        if (toStream)
            toFile << tape[i];
        std::cout << tape[i++];
    }

    if (toStream)
        toFile << "  :  " << command << std::endl;
    std::cout << "  :  " << command << std::endl;
}
