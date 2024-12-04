#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


bool isValidXPattern(vector<vector<char>> &vec, int i, int j)
{
    if(i<=0 || j<= 0 || i >= vec.size() -1 || j >= vec[0].size() - 1)
    {
        return false;
    }

    // Check all four possible combinations
    if ((vec[i-1][j-1] == 'M' && vec[i+1][j+1] == 'S' && vec[i-1][j+1] == 'M' && vec[i+1][j-1] == 'S') ||
        (vec[i-1][j-1] == 'S' && vec[i+1][j+1] == 'M' && vec[i-1][j+1] == 'S' && vec[i+1][j-1] == 'M') ||
        (vec[i-1][j-1] == 'M' && vec[i+1][j+1] == 'S' && vec[i-1][j+1] == 'S' && vec[i+1][j-1] == 'M') ||
        (vec[i-1][j-1] == 'S' && vec[i+1][j+1] == 'M' && vec[i-1][j+1] == 'M' && vec[i+1][j-1] == 'S')) {
        return true;
    }

    return false;
}

int countWordFound(vector<vector<char>> &vec)
{
    int maxRow = vec.size();
    int maxCol = vec[0].size();
    int count = 0;
    

    for(int i = 0; i < maxRow; i++)
    {
        for (int j = 0; j < maxCol; j++)
        {
            if(vec[i][j] == 'A')
            {
                if(isValidXPattern(vec, i, j))
                {
                    count++;
                }
            }
        }
    }
    return count;
}




int main()
{
    std:ifstream infile("input.txt");
    vector<vector<char>> xWord;

    if(!infile)
    {
        std::cerr << "Error reading file" << std::endl;
        return 1;
    }

    //Read each line, char by char and enter them into a 2 dimensional array.
    if(infile.is_open())
    {
        std::string line;
        while(std::getline(infile, line))
        {
            vector<char> row(line.begin(), line.end());
            xWord.push_back(row);
        }
    }
    infile.close();

    int total = countWordFound(xWord);

    cout << "Total Found words = " << total;
    return 0;

}