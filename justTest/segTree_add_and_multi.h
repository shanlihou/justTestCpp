#pragma once
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
static int mod = 1e9 + 7;

using namespace std;










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