#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <algorithm>
using namespace std;


int main()
{
    std:ifstream infile("input.txt");
    std::vector<int> numsA, numsB;
    int numA, numB, total;
    
    if(!infile)
    {
        std::cerr << "Error reading file" << std::endl;
        return 1;
    }

    while(infile >> numA >> numB)
    {
        numsA.push_back(numA);
        numsB.push_back(numB);
        std::sort(numsA.begin(), numsA.end());
        std::sort(numsB.begin(), numsB.end());
    }

    infile.close();

    for(int i=0; i< numsA.size(); i++)
    {
        total += abs(numsA[i] - numsB[i]);
    }

    std::cout<<total<<std::endl;

    return 0;
}