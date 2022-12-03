// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void solver(std::string input, std::string floatChars, const std::set<std::string>& dict, size_t index, std::set<std::string>& possWords);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // containter 
    std::set<std::string> answers;
    //copies inputs for helper function
    std::string myfloating = floating;
    std::string myinput = in;
    
    solver(myinput, myfloating, dict, 0, answers);
    //return valid words
    return answers;
}

void solver(std::string curr, std::string floating, const std::set<std::string>& dict, size_t index, std::set<std::string>& answers)
{
    //counts words to fill
    int dashes = 0;
    //basecase--> full size
    if(index == curr.size())
    {
        std::set<std::string>::iterator finder = dict.find(curr);
        if(floating.empty() && finder != dict.end()) 
        {
            answers.insert(curr); 
            return;
        }
        else return;
    }
    if(curr[index] != (char)45) 
    {
        solver(curr, floating, dict, index+1, answers);
        return;
    }
    for(size_t y = 0; y < curr.size(); y++)
    {
        if(curr[y] == (char)45)
        {
            dashes++;
        }
    }
    if(dashes > (int)floating.size())
    {
        for(int current = 97; current <= 122; current++)
        {
            if(floating.find((char)current) != std::string::npos) 
            {
                string tmp = floating;
                curr[index] = (char)current;
                tmp.erase(floating.find((char)current),1);
                solver(curr, tmp, dict, index, answers);
            }
            else if (floating.find((char)current) == std::string::npos)
            {
                curr[index] = (char)current;
                solver(curr, floating, dict, index+1, answers);
            }
        }
    }
    else
    {
        for(size_t w = 0; w < floating.size(); w++)
        {
            string tmp = floating;
            curr[index] = floating[w];
            tmp.erase(w,1);
            solver(curr, tmp, dict, index, answers);
        }
    }
}
