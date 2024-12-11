#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>



// Helper function to evaluate operations
long long evaluate(long long left, char op, long long right) {
    if (op == '+') {
        return left + right;
    } else if (op == '*') {
        return left * right;
    } else if (op == '|') {  // Concatenation operator
        std::string concatenated = std::to_string(left) + std::to_string(right);
        return stoll(concatenated); // Convert concatenated string back to number
    }
    return 0; // Should not reach here
}

// Recursive function to find valid expressions
void findValidExpressions(const std::vector<long long>& numbers, int index, long long currentValue, long long target, bool& found) {
    // Base case: if we've processed all numbers
    if (index == numbers.size()) {
        if (currentValue == target) {
            found = true; // Target found
        }
        return;
    }

    // Try all operators
    for (char op : {'+', '*', '|'}) {
        try {
            long long nextValue = evaluate(currentValue, op, numbers[index]);
            findValidExpressions(numbers, index + 1, nextValue, target, found);
        } catch (std::exception& e) {
            continue; // Handle any errors (like invalid concatenation)
        }
    }
}

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

// Main solver function
long long canBeDone(const std::vector<std::pair<long long, std::vector<long long>>>& problems) {
    long long runningTotal = 0;

    for (const auto& [target, numbers] : problems) {
        bool found = false;

        // Start recursive function
        findValidExpressions(numbers, 1, numbers[0], target, found);

        if (found) {
            runningTotal += target;
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
