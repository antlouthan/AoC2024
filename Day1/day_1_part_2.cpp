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
    int numA, numB, total, count = 0;
    
    if(!infile)
    {
        std::cerr << "Error reading file" << std::endl;
        return 1;
    }

    while(infile >> numA >> numB)
    {
        numsA.push_back(numA);
        numsB.push_back(numB);
    }

    infile.close();

    std::sort(numsA.begin(), numsA.end());
    std::sort(numsB.begin(), numsB.end());
    
    for(int i=0; i< numsA.size(); i++)
    {
        for(int j = 0; j <numsB.size(); j++)
        {
            if(numsB[j] > numsA[i])
            {
                total += numsA[i] * count;
                count = 0;
                break;
            }
            else if(numsB[j] == numsA[i])
            {
                count++;
            }
        }
    }

    std::cout<<total<<std::endl;

    return 0;
}