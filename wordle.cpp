#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordlehelper(const std::string& in,
                  const std::string& floating,
                  const std::set<std::string>& dict,
                  const std::vector<std::string>& possible,
                  std::string& current,
                  int index,
                  std::set<std::string>& result);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    int size = in.size();
    std::vector<std::string> possible(size);

    for (std::set<std::string>::const_iterator it = dict.begin(); it != dict.end(); ++it) {
        const std::string& temp = *it;
        if (temp.size() != size) {
        } else {
            bool fixed = true;
            for (int i = 0; i < size; ++i) {
                if (temp[i] != in[i] && in[i] != '-') {
                    fixed = false;
                    break;
                }
            }
            if (fixed) {
                for (int i = 0; i < size; ++i) {
                    if (in[i] == '-') {
                        char c = temp[i];
                        if (std::islower(c)) {
                            if(possible[i].find(c) == std::string::npos) {
                                possible[i].push_back(c);
                            }
                        }
                    }
                }
            }
        }
    }

    std::set<std::string> result;
    std::string current = in;
    wordlehelper(in, floating, dict, possible, current, 0, result);
    return result;
}

// Define any helper functions here
void wordlehelper( const std::string& in,
                   const std::string& floating,
                   const std::set<std::string>& dict,
                   const std::vector<std::string>& possible,
                   std::string& current, 
                   int index, 
                   std::set<std::string>& result) {
    int size = in.size();
    if (index == size) {
        std::string temp = current;
        for (int i = 0; i < floating.size(); ++i) {
            char tempc = floating[i];
            if (temp.find(tempc) == std::string::npos) {
                return;
            }
            temp[temp.find(tempc)] = '-';
        }
        if (dict.find(current) != dict.end()) {
            result.insert(current);
        }
        return;
    }

    if (in[index] != '-') {
        wordlehelper(in, floating, dict, possible, current, index + 1, result);
    } else {
        const std::string choice = possible[index];
        for(int i = 0; i < choice.size(); ++i) {
            current[index] = choice[i];
            wordlehelper(in, floating, dict, possible, current, index + 1, result);
        }
        current[index] = '-';
    }
}
