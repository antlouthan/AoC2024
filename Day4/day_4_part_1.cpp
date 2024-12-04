#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


bool isMatch(vector<vector<char>> &vec, int i, int j, int rowDir, int colDir)
{
    std::string target = "XMAS";
    int len = target.length();
    for(int k = 0; k < len; ++k)
    {
        int newRow = i + k * rowDir;
        int newCol = j + k * colDir;

        if(newRow < 0 || newRow >= vec.size() || newCol < 0 || newCol > vec[0].size() || vec[newRow][newCol] != target[k])
        {
            return false;
        } 
    }
    return true;
}

int countWordFound(vector<vector<char>> &vec)
{
    int maxRow = vec.size();
    int maxCol = vec[0].size();
    int count = 0;
    
    //Direction choices
    vector<pair<int,int>> directions = {
        {-1, 0},   // Up
        {1, 0},    // Down
        {0, -1},   // Left
        {0, 1},    // Right
        {-1, -1},  // Up Left
        {-1, 1},   // Up Right
        {1, -1},   // Down Left
        {1, 1}     // Down Right
    };

    for(int i = 0; i < maxRow; i++)
    {
        for (int j = 0; j < maxCol; j++)
        {
            if(vec[i][j] == 'X')
            {
                for (auto dir : directions)
                {
                    if(isMatch(vec, i, j, dir.first, dir.second))
                    {
                        count++;
                    }
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