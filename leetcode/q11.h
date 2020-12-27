#pragma once

int __builtin_popcount(int mask) {
    int ret = 0;
    while (mask) {
        if (mask & 1) {
            ret++;
        }

        mask >>= 1;
    }
    return ret;
}
// ------------------------------------ not use ---------------------------------------------------------------


#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
//template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef vector<ll> VLL;
typedef vector<int> VI;
typedef vector<vector<int>> VVI;
typedef set<int> SI;
#define PII pair<int,int>
#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define PLL pair<ll,ll>
#define MP make_pair
#define lowbit(x) ((x)&(-(x)))

#define CUR_LAST VI last(length, 0); VI cur(length, 0); VI* plast = &last; VI* pcur = &cur;

static int mod = 1e9 + 7;
#define REP(x, start, end) for(int x = start; x < end; x++)
#define RREP(x, start, end) for(int x = start - 1; x >= end; x--)
inline int twop(int x) { return 1 << x; };
int BitLength(unsigned int n)
{
    // pow of 2, 2^0 - 2 ^31 
    int powof2[32] =
    {
                 1,           2,           4,           8,         16,          32,
                64,         128,         256,         512,       1024,        2048,
              4096,        8192,       16384,       32768,      65536,      131072,
            262144,      524288,     1048576,     2097152,    4194304,     8388608,
          16777216,    33554432,    67108864,   134217728,  268435456,   536870912,
        1073741824
    };

    int left = 0;
    int right = 31;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (powof2[mid] <= n)
        {
            if (powof2[mid + 1] > n)
                return mid + 1; // got it! 
            else // powof2[mid] < n, search right part
                left = mid + 1;
        }

        else // powof2[mid] > n, search left part 
            right = mid - 1;
    }

    // not found  
    return -1;
}

class SegTree {
    VI data;
    int bitLen;
public:
    SegTree(int count): data((1 << BitLength(count)) * 2, 0), bitLen(BitLength(count)){

    };

    int recUpdate(int index, int deep) {
        if (deep == bitLen) {
            int _index = (1 << deep) - 1 + index;
            data[_index]++;
            return _index;
        }
        else {
            int subIndex = recUpdate(index, deep + 1);
            data[subIndex / 2]++;
            return subIndex / 2;
        }
    }

    void update(int index) {
        recUpdate(index, 0);
    }

    int getMax() {
        return 1 << bitLen;
    }

    int recGetSum(int l, int r, int s, int e, int p) {
        if (l <= s && e <= r) return data[p];
        int m = (s + e) / 2;
        int sum = 0;
        if (l <= m) sum = recGetSum(l, r, s, m, p * 2);
        if (r > m) sum += recGetSum(l, r, m + 1, e, p * 2 + 1);
        return sum;
    }

    int getSum(int l, int r) {
        if (r < l) {
            return 0;
        }
        return recGetSum(l, r, 1, 1 << bitLen, 1);
    }
};
int gcd(int x, int y)
{
    while (y ^= x ^= y ^= x %= y);
    return x;
}

class UnionFind {
    int n;
    vector<int> parent, size;
public:
    UnionFind(int n) {
        this->n = n;
        parent = vector<int>(n);
        size = vector<int>(n, 1);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }
    int find(int idx) {
        if (parent[idx] == idx)
            return idx;
        return parent[idx] = find(parent[idx]);
    }
    void connect(int a, int b) {
        int fa = find(a), fb = find(b);
        if (fa != fb) {
            if (size[fa] > size[fb]) {
                parent[fb] = fa;
                size[fa] += size[fb];
            }
            else {
                parent[fa] = fb;
                size[fb] += size[fa];
            }
        }
    }
};

class Solution {
public:
    int minMoves(vector<int>& nums, int k) {
        VI q;
        VI sums;
        int n = nums.size();
        int sum = 0;
        int j = 0;
        REP(i, 0, n) {
            if (nums[i]) {
                q.push_back(i - j);
                sum += i - j;
                sums.push_back(sum);
                j++;
            }
        }

        int count = k / 2;
        int result = INT_MAX;
        for (int i = 0; i + k <= q.size(); i++) {
            int mid = (2 * i + k - 1) / 2;
            int _q = q[mid];
            int sumi_1 = i == 0 ? 0 : sums[i - 1];
            int mis_1 = mid == 0 ? 0 : sums[mid - 1];
            int ret = (2 * (mid - i) - k + 1) * _q + sums[i + k - 1] - sums[mid] - mis_1 + sumi_1;
            result = min(result, ret);
        }
        return result;
    }
};