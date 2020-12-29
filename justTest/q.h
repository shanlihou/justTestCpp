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


class SegTree {
#define LAZY_DEF vector<PII> lazy;
#define LAZY_INIT lazy = vector<PII>(4 * n, MP(1, 0))
#define LAZY_UPDATE lazy[p] = MP(lazy[p].first * a % mod, ((ll)lazy[p].second * a + b) % mod)
#define LAZY_DOWN_DATA(data_p_2, data_p_2_1, lazy_p) \
    data_p_2 = ((ll)data_p_2 * lazy_p.first + (ll)lazy_p.second * (mid - start + 1)) % mod;\
    data_p_2_1 = ((ll)data_p_2_1 * lazy_p.first + (ll)lazy_p.second * (end - mid)) % mod;

#define LAZY_DOWN_LAZY(lazy_1, lazy_2, lazy_p) \
    lazy_1.first = (ll)lazy_1.first * lazy_p.first % mod;\
    lazy_1.second = ((ll)lazy_1.second * lazy_p.first + lazy_p.second) % mod;\
    lazy_2.first = (ll)lazy_2.first * lazy_p.first % mod;\
    lazy_2.second = ((ll)lazy_2.second * lazy_p.first + lazy_p.second) % mod;\
    lazy_p = MP(1, 0);

// not need modify ----------------------------------------------------------------
#define LAZY_DOWN if (lazy[p] != MP(1, 0)){\
    LAZY_DOWN_DATA(data[p * 2], data[p * 2 + 1], lazy[p])\
    LAZY_DOWN_LAZY(lazy[p * 2], lazy[p * 2 + 1], lazy[p])\
}

#define LAZY_DOWN_GET if (lazy[p] != MP(1, 0) && start != end){\
    LAZY_DOWN_DATA(data[p * 2], data[p * 2 + 1], lazy[p])\
    LAZY_DOWN_LAZY(lazy[p * 2], lazy[p * 2 + 1], lazy[p])\
}


private:
    vector<uint> data;
    LAZY_DEF
    int _size;
    void build(int start, int end, int p, vector<int>& origin) {
        if (start == end) {
            data[p] = origin[start];
            return;
        }
        int mid = (start + end) / 2;
        build(start, mid, p * 2, origin);
        build(mid + 1, end, p * 2 + 1, origin);
        data[p] = data[p * 2] + data[(p * 2) + 1];
    }

    int _getsum(int left, int right, int start, int end, int p) {
        // [left,right] 为查询区间,[start,end] 为当前节点包含的区间,p为当前节点的编号
        if (left <= start && end <= right)
            return data[p];
        // 当前区间为询问区间的子集时直接返回当前区间的和
        int mid = (start + end) / 2;
        LAZY_DOWN
        int sum = 0;
        if (left <= mid) sum = _getsum(left, right, start, mid, p * 2);
        if (right > mid) sum += _getsum(left, right, mid + 1, end, p * 2 + 1);
        return sum;
    }

    void _update(int left, int right, ll a, ll b, int start, int end, int p) {
        // [left,right] 为修改区间,c 为被修改的元素的变化量,[start,end] 为当前节点包含的区间,p
        // 为当前节点的编号
        if (left <= start && end <= right) {
            data[p] = (data[p] * a + (end - start + 1) * b) % mod;
            LAZY_UPDATE;
            return;
        }  // 当前区间为修改区间的子集时直接修改当前节点的值,然后打标记,结束修改
        int mid = (start + end) / 2;
        LAZY_DOWN_GET

        if (left <= mid) _update(left, right, a, b, start, mid, p * 2);
        if (right > mid) _update(left, right, a, b, mid + 1, end, p * 2 + 1);
        data[p] = (data[p * 2] + data[p * 2 + 1]) % mod;
    }
public:
    SegTree(int n) {
        data = vector<uint>(4 * n, 0);
        LAZY_INIT;
        _size = n;
    }

    SegTree(vector<int>& origin) {
        int n = origin.size();
        _size = n;
        data = vector<uint>(4 * n, 0);
        LAZY_INIT;
        build(0, n - 1, 1, origin);
    }

    int getSum(int left, int right) {
        return _getsum(left, right, 0, _size - 1, 1);
    }

    void update(int left, int right, int a, int b) {
        _update(left, right, a, b, 0, _size - 1, 1);
    }
};

#define MAX_NUM 100000

class Fancy {
    SegTree st;
    int _size;
public:
    Fancy() : st(SegTree(MAX_NUM)), _size(0) {
    }

    void append(int val) {
        st.update(_size, _size, 1, val);
        _size++;
    }

    void addAll(int inc) {
        if (_size) {
            st.update(0, _size - 1, 1, inc);
        }
    }

    void multAll(int m) {
        if (_size) {
            st.update(0, _size - 1, m, 0);
        }
    }

    int getIndex(int idx) {
        if (idx >= _size) {
            return -1;
        }
        return st.getSum(idx, idx);
    }
};
