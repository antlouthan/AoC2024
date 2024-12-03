#include <iostream>
#include <fstream>
#include <regex>
#include <string>
using namespace std;

int main() {
    ifstream infile("input.txt");
    int total = 0;
    std::regex regex_pattern(R"(mul\(\d{1,3},\d{1,3}\))");
    std::smatch matches;

    if (!infile) {
        std::cerr << "Error reading file" << std::endl;
        return 1;
    }

    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::string::const_iterator search_start(line.cbegin());
            while (std::regex_search(search_start, line.cend(), matches, regex_pattern)) {
                // Extracting x and y from the match
                std::string match_str = matches[0].str();
                size_t comma_pos = match_str.find(',');
                int x = std::stoi(match_str.substr(4, comma_pos - 4));  // Extract x after "mul("
                int y = std::stoi(match_str.substr(comma_pos + 1, match_str.size() - comma_pos - 2));  // Extract y

                // Print and accumulate
                std::cout << "mul(" << x << "," << y << ")" << " -> x: " << x << ", y: " << y << std::endl;
                total += x * y;

                search_start = matches.suffix().first; // Move past the current match
            }
        }
    }

    infile.close();
    std::cout << "Total: " << total << std::endl;

    return 0;
}
