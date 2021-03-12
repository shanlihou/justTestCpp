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
    return ret;
}
// ------------------------------------ not use ---------------------------------------------------------------

#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <functional>
#include <set>
#include <tuple>
#include <stack>
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
typedef vector<string> VS;
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
int g_dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
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

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
ll cnn(int n1, int n2) {
    int ret = 1;
    REP(i, 0, n2) {
        ret *= (n1 - i);
        ret /= (1 + i);
    }
    return ret;
}
/* code down------------------------------------------------------------------------------- */

inline int ABS(int val) {
    return val >= 0 ? val : -val;
}

#define PRE (*_pre)
#define CUR (*_cur)

struct classcomp {
    bool operator() (const PII& lhs, const PII& rhs) const
    {
        if (lhs.first == rhs.first)
            return lhs.second < rhs.second;

        return lhs.first < rhs.first;
    }
};

void dijkstra(int n, VVI& edges, VI& dis, vector<vector<PII>>& adj) {
    VI mark(n, 0);
    set<PII, classcomp> _pq;
    for (auto& i : edges) {
        int x = i[0] - 1;
        int y = i[1] - 1;
        adj[x].emplace_back(MP(y, i[2]));
        adj[y].emplace_back(MP(x, i[2]));
        if (i[0] == n) {
            _pq.insert(MP(i[2], y));
            dis[y] = i[2];
        }
        else if (i[1] == n)
        {
            _pq.insert(MP(i[2], x));
            dis[x] = i[2];
        }
    }


    while (_pq.size()) {
        PII small = *_pq.begin();
        _pq.erase(small);
        mark[small.second] = 1;

        for (auto& i : adj[small.second]) {
            if (mark[i.first]) {
                continue;
            }

            if (i.first == n - 1) {
                continue;
            }

            if (dis[i.first] > small.first + i.second) {
                if (dis[i.first] != INT_MAX) {
                    _pq.erase(MP(dis[i.first], i.first));
                }
                dis[i.first] = small.first + i.second;
                _pq.insert(MP(dis[i.first], i.first));
            }
        }
    }
}


class Trie {
public:
    map<int, Trie> sons;
    int leaf;
    Trie(): leaf(-1) {

    }

    void iterBySize(int len, function<void(int)> const& f) {
        if (len == 0) {
            if (leaf != -1) {
                f(leaf);
            }
            return;
        }
        for (auto& i : sons) {
            i.second.iterBySize(len - 1, f);
        }
    }

    void iterBySize(string &str, int len, function<void (int)> const &f) {
        auto cur = this;
        for (auto& i : str) {
            int c = i - 'a';
            if (!cur->sons.count(c)) {
                return;
            }


            cur = &cur->sons[c];
        }

        cur->iterBySize(len - str.size(), f);
    }

    void iterAll(function<void(int)> const &f) {
        if (leaf != -1) {
            f(leaf);
        }

        for (auto& i : sons) {
            i.second.iterAll(f);
        }
    }

    bool checkHasStr(int len) {
        if (len == 0) {
            return leaf != -1;
        }

        for (auto& i : sons) {
            if (i.second.checkHasStr(len - 1))
                return true;
        }

        return false;
    }

    bool checkHasStr(string& str, int len) {
        auto cur = this;
        for (auto& i : str) {
            int c = i - 'a';
            if (!cur->sons.count(c)) {
                return false;
            }


            cur = &cur->sons[c];
        }

    }
};

class Solution {
public:
    Trie root;
    vector<string> words;
    vector<int> stH;
    vector<int> stV;
    int lenH;
    int lenV;
    map<int, VI> len2i;
    int dfs() {
        if (stH.size() > stV.size()) {
            int idx = stV.size();
            string str;
            for (auto& i : stH) {
                str += words[i][idx];
            }

            auto f = [&](int leaf) {
                stV.emplace_back(leaf);
                dfs();
                stV.pop_back();
            };

            if (!stV.size()) {
                int c = words[stH[0]][0] - 'a';
                root.sons[c].iterAll(f);
            }
        }
        else {
            int idx = stH.size();
            string str;
            for (auto& i : stV) {
                str += words[i][idx];
            }

            auto f = [&](int leaf) {
                string& curStr = words[leaf];
                REP(i, stV.size(), lenH) {
                    string _str;
                    for (auto& j : stH) {
                        _str += words[j][i];
                    }
                    _str += curStr[i];
                    root.checkHasStr(_str, lenV);
                }

            };
            root.iterBySize(str, lenH, f);
        }
    }
    vector<string> maxRectangle(vector<string>& words) {
        int n = words.size();
        this->words = words;
        REP(i, 0, n) {
            Trie* cur = &root;
            REP(j, 0, words.size()) {
                int c = words[i][j] - 'a';
                if (!cur->sons.count(c)) {
                    cur->sons[c] = Trie();
                }

                cur = &cur->sons[c];
            }
            len2i[words.size()].emplace_back(i);
            cur->leaf = i;
        }

        REP(i, 0, n) {
            stH.emplace_back(i);
            lenH = words[i].size();
            int c = words[i][0] - 'a';
            auto f = [&](int leaf) {
                stV.emplace_back(leaf);
                lenV = words[leaf].size();
                dfs();
                stV.pop_back();
            };
            root.sons[c].iterAll(f);
            stH.pop_back();
        }
    }
};