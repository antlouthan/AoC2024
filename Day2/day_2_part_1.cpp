#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <sstream>
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




int main()
{
    std:ifstream infile("input.txt");
    int total = 0;
    std::vector<int> nums;
    
    if(!infile)
    {
        std::cerr << "Error reading file" << std::endl;
        return 1;
    }

    if(infile.is_open())
    {
        std::string line;
        while(std::getline(infile, line))
        {
            std::stringstream ss(line);
            int num;
            while(ss >> num)
            {
                nums.push_back(num);
            }
            if(isMonotonicWithinRange(nums))
            {
                total++;
            }
            nums.clear();
        }
    }


    

    infile.close();

    std::cout<<total<<std::endl;

    return 0;
}