#pragma once
#include <vector>
using namespace std;

class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        auto length = nums.size();
        vector<vector<int>> a (length, vector<int>(4, 0));

        int sumOdd = 0;
        int sumDouble = 0;
        for (int i = 0; i < length; i++) {
            a[i][0] = sumOdd;
            a[i][1] = sumDouble;
            if (i & 1) {
                sumOdd += nums[i];
            }
            else {
                sumDouble += nums[i];
            }
        }
        sumOdd = 0;
        sumDouble = 0;
        for (int i = length - 1; i >= 0; i--) {
            a[i][2] = sumOdd;
            a[i][3] = sumDouble;
            if (i & 1) {
                sumDouble += nums[i];
            }
            else {
                sumOdd += nums[i];
            }
        }

        int count = 0;

        for (int i = 0; i < length; i++) {
            if (a[i][0] + a[i][2] == a[i][1] + a[i][3]) {
                count++;
            }
        }
        return count;
    }
};