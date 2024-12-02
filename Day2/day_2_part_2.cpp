#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

bool isMonotonicWithinRange(vector<int>& vec) {
    if (vec.size() < 2) {
        return true;
    }

    bool increasing = vec[0] < vec[1];
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        int diff = vec[i + 1] - vec[i];
        if (increasing) {
            if (diff < 1 || diff > 3) {
                return false;
            }
        } else {
            if (diff > -1 || diff < -3) {
                return false;
            }
        }
    }
    return true;
}

bool isSafeWithDampener(vector<int> vec) {
    if (isMonotonicWithinRange(vec)) {
        return true;
    }

    for (size_t i = 0; i < vec.size(); ++i) {
        vector<int> temp = vec;
        temp.erase(temp.begin() + i);
        if (isMonotonicWithinRange(temp)) {
            return true;
        }
    }

    return false;
}

int main() {
    ifstream infile("input.txt");
    int total = 0;
    vector<int> nums;

    if (!infile) {
        cerr << "Error reading file" << endl;
        return 1;
    }

    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            stringstream ss(line);
            int num;
            while (ss >> num) {
                nums.push_back(num);
            }
            if (isSafeWithDampener(nums)) {
                total++;
            }
            nums.clear();
        }
    }

    infile.close();

    cout << total << endl;

    return 0;
}
