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


class Solution {
public:
    VVI matV;
    VVI matH;
    int recGetVal(int x, int y, VVI& ret) {
        if (ret[x][y] != 0) {
            return ret[x][y];
        }

        if (matV[x][y] == x && matH[x][y] == y) {
            return ret[x][y] = 1;
        }
        else if (matV[x][y] == x) {
            return ret[x][y] = recGetVal(x, matH[x][y], ret) + 1;
        }
        else if (matH[x][y] == y) {
            return ret[x][y] = recGetVal(matV[x][y], y, ret) + 1;
        }

        int v = recGetVal(matV[x][y], y, ret);
        int h = recGetVal(x, matH[x][y], ret);
        return ret[x][y] = max(v, h) + 1;
    }

    vector<vector<int>> matrixRankTransform(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        VVI _matV(m, VI(n, 0));
        VVI _matH(m, VI(n, 0));
        matV = move(_matV);
        matH = move(_matH);

        REP(i, 0, m) {
            vector<PII> tmp;
            REP(j, 0, n) {
                tmp.push_back(MP(mat[i][j], j));
            }
            sort(all(tmp));
            matH[i][tmp[0].second] = tmp[0].second;
            REP(j, 1, n) {
                if (tmp[j].first == tmp[j - 1].first) {
                    if (tmp[j - 1].second == tmp[j - 1].second)
                        matH[i][tmp[j].second] = tmp[j].second;
                    else
                        matH[i][tmp[j].second] = matH[i][tmp[j - 1].second];
                }
                else {
                    matH[i][tmp[j].second] = tmp[j - 1].second;
                }
            }
        }


        REP(j, 0, n) {
            vector<PII> tmp;
            REP(i, 0, m) {
                tmp.push_back(MP(mat[i][j], i));
            }
            sort(all(tmp));
            matV[tmp[0].second][j] = tmp[0].second;
            REP(i, 1, n) {
                if (tmp[i].first == tmp[i - 1].first) {
                    if (matV[tmp[i - 1].second][j] == tmp[i - 1].second)
                        matV[tmp[i].second][j] = tmp[i].second;
                    else
                        matV[tmp[i].second][j] = matV[tmp[i - 1].second][j];
                }
                else {
                    matV[tmp[i].second][j] = tmp[i - 1].second;
                }
            }
        }

        VVI ret(m, VI(n, 0));
        REP(i, 0, m) {
            REP(j, 0, n) {
                if (ret[i][j]) {
                    continue;
                }

                if (matV[i][j] == i && matH[i][j] == j) {
                    ret[i][j] = 1;
                }

                recGetVal(i, j, ret);
            }
        }

        return ret;
    }
};