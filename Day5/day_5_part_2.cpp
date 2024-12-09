#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <algorithm>
#include <sstream>
using namespace std;

int findMiddleNum(std::vector<int> vec)
{
    int midPoint = (vec.size() - 1) / 2;

    return vec[midPoint];
}

std::vector<std::vector<int>> fixInvalidLines(std::vector<std::vector<int>> lines, std::vector<std::pair<int, int>> rules)
{
    // loop through the vector of vectors starting at the first row. 
    for(int i = 0; i < lines.size(); i++)
    {
        // Loop through the vector of ints starting at the last element and working towards the front. 
        for(int j = lines[i].size() - 1; j >= 0; j--)
        {
            std::vector<std::pair<int, int>> foundRules; // New smaller vector to add in the valid rules JUST for this element. 
            //Find all the rules that pertain to this element. 
            for(auto pr : rules)
            {
                if(pr.first == lines[i][j])
                {
                    foundRules.push_back({pr.first, pr.second});
                }
            }
            //Check if any of the elements before the current one violate a rule, if they do, perform a swap on those elements.
            bool breakFlag = false;
            for(auto rulePairs : foundRules)
            { 
                if(breakFlag == true)
                {
                    break;
                }
                for(int k = 0; k < j; k++)
                {
                    if(lines[i][k] == rulePairs.second)
                    {
                        //Perform swap of [i][j] with [i][k]
                        std::swap(lines[i][j], lines[i][k]);
                        j = lines[i].size();
                        breakFlag = true;
                        break;
                    }
                }
            }

            
        }
    }
    

    return lines;
}

std::vector<std::vector<int>> checkValidLines(std::vector<std::vector<int>> pages, std::vector<std::pair<int, int>> rules)
{
    std::vector<std::vector<int>> invalidLines;
    //Rules for update: 
    // If a page update line includes BOTH pages in a rule, then the rule MUST be observed. If not, it doesn't matter. 
    

    //So we need to actually know all of the pages/the order they are put in for the update. This is represented in the pages vector per row. 
    // If we start at the back, we can look to see if the page is in the rules, 
    //    and then check if any of the rules are violated by seeing if any of the matching rule pages are in this line.
    // If we get to the beginning of the row in the vector then we should be valid and can push that row to the validLines vector. 

    // Loop through the 2D vector rows incrementally
    for(int i = 0; i < pages.size(); i++)
    {
        bool isLineValid = true;
        //loop through the individual row backwards. 
        for (int j = pages[i].size()-1; j >=0; j--)
        {
            //Need to grab all rules where the first of the pair equals the current element of the updates vector.
            //Then we need to check all the elements within the updates vector to see if any of the second of the pair comes before it, IF it exists within the updates vector. If so, this line is bad. 

            std::vector<std::pair<int, int>> foundRules; // New smaller vector to add in the valid rules JUST for this element. 
            for(auto pr : rules)
            {
                if(pr.first == pages[i][j])
                {
                    foundRules.push_back({pr.first, pr.second});
                }
            }
            //Now we have a smaller vector of pairs of rules that only pertain to this specific element. 
            // now we have to check each second of the pairs to see if any of them appear before the current element. 
            
            for(auto validPairs : foundRules)
            {
              for(int k = 0; k < j; k++)
              {
                if(pages[i][k] == validPairs.second)
                {
                    isLineValid = false;
                    break;
                }
              }
            }
        }
        if(!isLineValid)
        {
            invalidLines.push_back(pages[i]);
        }
        
    }

    return fixInvalidLines(invalidLines, rules);
}

int main()
{
    std::ifstream rules("rules.txt");
    std::ifstream updates("updates.txt");

    std::vector<std::pair<int, int>> rulesVec;
    std::vector<std::vector<int>> updatesVec;

    int total = 0;

    if(!rules || !updates)
    {
        std::cerr << "Error reading file" << std::endl;
        return 1;
    }

    if(rules.is_open())
    {
        std::string line;
        while(std::getline(rules, line))
        {
            std::replace(line.begin(), line.end(), '|', ' ');
            std::stringstream ss(line);
            int numA, numB;

            while(ss >> numA >> numB)
            {
                rulesVec.push_back({numA, numB});
            }
        }
    }
    rules.close();

    if(updates.is_open())
    {
        std::string line;
        while(std::getline(updates, line))
        {
            std::replace(line.begin(), line.end(), ',', ' ');
            std::stringstream ss(line);
            int num;
            vector<int> tmpVec;
            while(ss >> num)
            {
                tmpVec.push_back(int(num));
            }
            updatesVec.push_back(tmpVec);
        }
    }

    updates.close();
   
    std::vector<std::vector<int>> validOps = checkValidLines(updatesVec, rulesVec);

    for(const auto &r : validOps)
    {
        total += findMiddleNum(r);
    }
    cout << "The total of all middle numbers is: " << total;
    return 0;
}