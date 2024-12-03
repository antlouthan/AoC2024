#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using namespace std;

std::string extractBetweenDoAndDont(const std::string& str) {
    // Regex to handle text between do and don't
    std::regex regex(R"(\bdo\b(.*?)(?=\bdon't\b))", std::regex::icase);
    std::smatch matches;
    std::string result;

    // Check for "do" at the very beginning of the string manually so that it's easier to perform the rest of the operations
    if (str.substr(0, 2) == "do" || str.substr(0, 2) == "Do") {
        size_t dont_pos = str.find("don't", 2);
        if (dont_pos != std::string::npos) {
            std::string between = str.substr(2, dont_pos - 2);
            result += between;
        }
    }

    // Rest of string after first do/don't split. 
    std::string::const_iterator search_start(str.cbegin());
    while (std::regex_search(search_start, str.cend(), matches, regex)) {
        result += matches[1].str(); // Append the captured text between "do" and "don't"
        search_start = matches.suffix().first; // Move past the current match to avoid overlapping
    }

    return result;
}

int main() {
    ifstream infile("input.txt");
    int total = 0;
    std::regex regex_pattern(R"(mul\(\d{1,3},\d{1,3}\))");
    std::smatch matches;
    std::string inputStr = "do"; //add do to the beginning here since the instructions say to begin with capture enabled, this makes it easier for the regex logic later. 
    std::string validStr;

    if (!infile) {
        std::cerr << "Error reading file" << std::endl;
        return 1;
    }

    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            inputStr += line;
        }
    }
    infile.close();

    validStr += extractBetweenDoAndDont(inputStr);
    std::string::const_iterator search_start(validStr.cbegin());
    while (std::regex_search(search_start, validStr.cend(), matches, regex_pattern)) {
        // Extracting x and y from the match
        std::string match_str = matches[0].str();
        size_t comma_pos = match_str.find(',');
        int x = std::stoi(match_str.substr(4, comma_pos - 4));  // Extract x after "mul("
        int y = std::stoi(match_str.substr(comma_pos + 1, match_str.size() - comma_pos - 2));  // Extract y

        // Accumulate the product
        total += x * y;

        search_start = matches.suffix().first; // Move past the current match
    }
    
    std::cout << "Total: " << total << std::endl;

    return 0;
}
