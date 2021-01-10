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

int __builtin_ctz(int val) {
    int ret = 0;
    while ((val & 1 << ret) == 0) {
        ret++;
    }
    return ret - 1;
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
typedef unsigned int uint;
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
    VVI linkList;
    int curMask;
    int cityNum;
public:
    pair<int, int> dfs(int u, int deep, int last) {
        int deep1 = -1, deep2 = -1;
        int maxDis = -1, maxDeep = -1;
        cityNum++;
        for (auto& i : linkList[u]) {
            if (curMask & 1 << i && i != last) {
                auto ret = dfs(i, deep + 1, u);
                maxDis = max(maxDis, ret.first);
                maxDeep = max(maxDeep, ret.second);

                if (deep1 < ret.second) {
                    deep2 = deep1;
                    deep1 = ret.first;
                }
                else if (deep2 < ret.second) {
                    deep2 = ret.second;
                }
            }
        }

        maxDis = max(maxDis, maxDeep);
        if (deep1 != -1 && deep2 != -1) {
            maxDis = max(maxDis, deep1 + deep2 - 2 * deep);
        }
        return MP(maxDis, maxDeep);
    }

    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        linkList = VVI(n, VI());
        for (auto& i : edges) {
            linkList[i[0] - 1].push_back(i[1] - 1);
            linkList[i[1] - 1].push_back(i[0] - 1);
        }

        VI ret(n - 1, 0);
        for (curMask = 1; curMask < 1 << n; curMask++) {
            cityNum = 0;
            auto retPair = dfs(__builtin_ctz(curMask), 0, -1);
            if (cityNum == __builtin_popcount(curMask) && retPair.first > 0) {
                ret[retPair.first - 1]++;
            }
        }
        return ret;
    }
};