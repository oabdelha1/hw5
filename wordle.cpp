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
void wordinator(const string& in, const string& floating, const set<std::string>& dict, int len, set<string>& finaldict, string word, vector<char> floatingChars);
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

    vector<char> floatingChars;

    for(size_t i = 0; i < floating.size(); i++) {
        floatingChars.push_back(floating[i]);
    }
    cout << "test " << endl;
    wordinator(in, floating, dict, 0, finaldict, "", floatingChars);
    return finaldict;
}

// Define any helper functions here

void wordinator(const std::string& in, const std::string& floating, const std::set<std::string>& dict, int len, set<string>& finaldict, string word, vector<char>floatingChars){

    //Base Case
    cout << "Hi" << endl;
    if (len == in.length()){
        if (dict.find(word)!=dict.end()) {
            finaldict.insert(word);
        }
        return;
    }

    //If current index has letter, add letter
    if (in[len] != '-'){
        word+= in[len];
        wordinator(in, floating, dict, len+1, finaldict, word, floatingChars);
    }
    else {
        if(calcbars(in, len) == floatingChars.size()) {
            vector<char> temp = floatingChars;
            for (size_t i = 0; i < floatingChars.size(); i ++){
                word += floatingChars[i];
                temp.erase(temp.begin()+i);
                wordinator(in, floating, dict, len+1, finaldict, word, floatingChars);
                floatingChars = temp;
            }
        }
        else {
            vector<char>temp = floatingChars;
            for (int i = 97; i < 123; i++) {
                vector<char>::iterator charloc = find(floatingChars.begin(), floatingChars.end(), char(i));
                if (charloc != floatingChars.end()) {
                    cout <<"seg fault b" << endl;
                    temp.erase(charloc);
                    word += char(i);
                    wordinator(in, floating, dict, len + 1, finaldict, word, floatingChars);
                    floatingChars = temp;
                }
                else {
                    cout << "seg fault a" << endl;
                    word += char(i);
                    wordinator(in, floating, dict, len+1, finaldict, word, floatingChars);
                }
            }
        }
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