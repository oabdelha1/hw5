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
void wordinator(string &in, const set<string>& dict, set<string>& finaldict, size_t len, map<char, int> floatingChars, int floatingCount, int dash);
size_t calcbars(const std::string& in, int len);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> finaldict;

    //Setup by length
    /*
    for(set<string>::iterator it = dict.begin(); it != dict.end(); it++){
        if (it->length() == in.length()){
            finaldict.insert(*it);
        }
    }
     */

    map<char, int> floatingChars;
    int floatcount = 0;
    for (size_t i = 0; i < floating.size(); i++) {
        floatingChars[floating[i]]++;
        floatcount++;
    }

    int dash = 0;
    for(int i = 0; i < in.size(); i++){
        if (in[i] == '-') dash++;
    }

    cout << "test a" << endl;
    string incopy = in;
    //wordinator(incopy, floating, dict, finaldict, dash, 0, floatingChars, floatcount);
    wordinator(incopy, dict, finaldict, 0, floatingChars, floatcount, dash);
    return finaldict;
}

// Define any helper functions here

void wordinator(string &in, const set<string>& dict, set<string>& finaldict, size_t len, map<char, int> floatingChars, int floatingCount, int dash){
    if (len >= in.length()) {
        if (dict.find(in) != dict.end()) {
            finaldict.insert(in);
        }
        return;
    }

    // If current index has a letter, add letter
    if (in[len] != '-') {
        wordinator(in, dict, finaldict, len + 1, floatingChars, floatingCount, dash);
    } else {
        for (int i = 97; i < 123; i++) {
            in[len] = char(i);

            // Case: Floating character
            if (floatingChars[char(i)] > 0) {
                floatingChars[char(i)]--;
                wordinator(in, dict, finaldict, len + 1, floatingChars, floatingCount - 1, dash-1);
                floatingChars[char(i)]++;
            }
                // Case: Non-floating character
            else if (floatingCount < dash) {
                wordinator(in, dict, finaldict, len + 1, floatingChars, floatingCount, dash-1);
            }
        }
        // Restore the original character at position len
        in[len] = '-';
    }
}


size_t calcbars(const std::string& in, int len){
    int dashes = 0;
    for (size_t i = len; i < in.length(); i++){
        if (in[i] == '-'){
            dashes++;
        }
    }

    return dashes;
}