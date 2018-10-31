#include <iostream>
#include <fstream>
#include <vector>
#include "input-validator.hpp"
#include "turing-machine.hpp"

struct argument {
    std::string command;
    bool hasArgument;
    std::string description;
    bool isUsed;
};

bool isCharANumber(char ch) {
    auto * nums = const_cast<char *>("0123456789");
    for (int i = 0; i < 10; ++i)
        if (ch == nums[i])
            return true;
    return false;
}

bool isNumCharArray(const char *array) {
    int cnt = 0;
    char ch;
    while ((ch = array[cnt++])) {
        if (!isCharANumber(ch) || cnt > 1)
            return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    int result = 1;
    int dimension;

    std::ifstream matrixFile;
    std::ifstream tapeFile;

    std::vector<char> matrix;
    std::vector<char> tape;

    InputValidator inputValidator;
    TuringMachine turingMachine(std::move(matrix), std::move(tape), dimension);
    char* args[4];
    bool isMatrixSetted = false;
    argument arguments[] {
            {"-f", true, "Opens and reading matrix from file", false},
            {"-c", true, "Dimension of matrix", false},
            {"-t", true, "Tape from file", false},
            {"er", false, "Error", true}
    };
    // Reading arguments
    for (int i = 1; i < argc; i++) {
        if (argv[i] != arguments[0].command && argv[i] != arguments[1].command &&
            argv[i] != arguments[2].command) {
            std::cout << "Error occurred on parsing arguments" << std::endl;
            goto returnLabel;
        }
        if ((argv[i] == arguments[0].command && arguments[0].isUsed) ||
            (argv[i] == arguments[1].command && arguments[1].isUsed) ||
            (argv[i] == arguments[2].command && arguments[2].isUsed)) {
            std::cout << "Multiple argument initialization" << std::endl;
            goto returnLabel;
        }
        if (argv[i] == arguments[0].command && !isMatrixSetted &&
            !arguments[0].isUsed && !arguments[1].isUsed && argc > i+1) {
            isMatrixSetted = true;
            arguments[0].isUsed = true;
            args[0] = argv[++i];
        }
        else if (argv[i] == arguments[1].command && !isMatrixSetted &&
                   !arguments[1].isUsed && !arguments[0].isUsed && argc > i+1) {
            isMatrixSetted = true;
            arguments[1].isUsed = true;
            args[3] = argv[++i];
            if (!isNumCharArray(args[3])) {
                std::cout << "Value in \"-c\" isn't positive integer less then 10" << std::endl;
            }
            dimension = std::atoi(args[3]);
        }
        else if (argv[i] == arguments[2].command && !arguments[2].isUsed && argc > i+1) {
            arguments[2].isUsed = true;
            args[1] = argv[++i];
        }
        else {
            std::cout << "Error occurred on parsing arguments" << std::endl;
            goto returnLabel;
        }
    }
    if (!arguments[0].isUsed && !arguments[1].isUsed && !arguments[2].isUsed) {
        std::cout << R"(Didn't initialized matrix in arguments, use "-c" for value or "-f" for file!)" << std::endl;
        goto returnLabel;
    }
    if (!inputValidator.validateMatrix(&matrix, &tape, args, &dimension,
                                      arguments[0].isUsed, arguments[2].isUsed))
        goto returnLabel;

    turingMachine.execute();

    result = 0;
    returnLabel:
    return result;
}
