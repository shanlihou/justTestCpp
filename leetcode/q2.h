#pragma once
#include <string>
using namespace std;

class Solution {
public:
    string getSmallestString(int n, int k) {
        int left = k - n;
        char* _ret = new char[n + 1];
        for (int i = n - 1; i >= 0; i--) {
            if (left >= 25) {
                left -= 25;
                _ret[i] = 'a' + 25;
            }
            else if (left > 0) {
                _ret[i] = 'a' + left;
                left = 0;
            }
            else {
                _ret[i] = 'a';
            }
        }
        _ret[n] = 0;
        string ret = string(_ret);
        delete[] _ret;
        return ret;
    }
};