#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

// Parse a single line long longo a pair<long long, vector<long long>>
std::pair<long long, std::vector<long long>> parseLine(const std::string& line) {
    std::istringstream stream(line);
    long long firstNumber;
    stream >> firstNumber;

    std::vector<long long> remainingNumbers;
    long long num;
    while (stream >> num) {
        remainingNumbers.push_back(num);
    }

    return {firstNumber, remainingNumbers};
}

// Evaluate one combination of operators
bool evaluateCombination(const std::vector<long long>& numbers, const std::vector<char>& operators, long long target) {
    long long result = numbers[0];
    for (size_t i = 0; i < operators.size(); ++i) {
        if (operators[i] == '+') {
            result += numbers[i + 1];
        } else if (operators[i] == '*') {
            result *= numbers[i + 1];
        }
    }
    return result == target;
}

// Main solver function
long long canBeDone(const std::vector<std::pair<long long, std::vector<long long>>>& problems) {
    long long runningTotal = 0;

    for (const auto& [target, numbers] : problems) {
        long long numOperators = numbers.size() - 1;
        long long totalCombinations = 1 << numOperators;

        bool found = false;
        

        // Iterate through all operator combinations
        for (long long i = 0; i < totalCombinations; ++i) {
            std::vector<char> operators;
            for (long long j = 0; j < numOperators; ++j) {
                if (i & (1 << j)) {
                    operators.push_back('*');
                } 
                else if{
                    operators.push_back('+');
                }
            }

            // Evaluate this combination
            if (evaluateCombination(numbers, operators, target)) {

                runningTotal += target;
                found = true;
                break; // Stop checking once a valid combination is found
            }
        }
    }

    return runningTotal;
}

int main() {
    std::vector<std::pair<long long, std::vector<long long>>> equations;
    std::ifstream infile("input.txt");

    if (!infile) {
        std::cerr << "Error reading file" << std::endl;
        return 1;
    }

    // Parse the input file
    std::string line;
    while (std::getline(infile, line)) {
        line.erase(std::remove(line.begin(), line.end(), ':'), line.end());
        equations.push_back(parseLine(line));
    }

    infile.close();

    // Solve and prlong long the result
    long long runningTotal = canBeDone(equations);
    std::cout << "The total of all valid equations is: " << runningTotal << std::endl;

    return 0;
}
