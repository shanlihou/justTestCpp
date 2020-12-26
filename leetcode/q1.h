#pragma once
#include <vector>
#include <string>
using namespace std;


class Iter {

public :
    Iter(vector<string>& word) :word(word), index(0), isValid(false){
        if (word.size() > 0) {
            this->_iter = word[0].begin();
            isValid = true;
        }
    }
    
    char getnext() {
        char ret = 0;
        if (isValid) {
            ret = *_iter;
        }
        else {
            return 0;
        }

        _iter++;
        if (_iter == word[index].end()) {
            index++;
            if (index >= word.size()) {
                isValid = false;
            }
            else {
                _iter = word[index].begin();
            }
        }
        return ret;
    }
    
    int index;
    vector<string>& word;
    string::iterator _iter;
    bool isValid;
};


class Solution {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        auto iter1 = Iter(word1);
        auto iter2 = Iter(word2);

        while (true)
        {
            char next1 = iter1.getnext();
            char next2 = iter2.getnext();
            if (next1 != next2) {
                return false;
            }

            if (next1 == 0) {
                return true;
            }
        }
    }
};