#pragma once
#include <vector>
using namespace std;

class SegTree {
private:
	vector<int> data;
	int _size;
	void build(int start, int end, int p, vector<int> &origin) {
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
		// [left,right] 为查询区间,[start,end] 为当前节点包含的区间,p 为当前节点的编号
		if (left <= start && end <= right)
			return data[p];  // 当前区间为询问区间的子集时直接返回当前区间的和
		int m = (start + end) / 2, sum = 0;
		if (left <= m) sum += _getsum(left, right, start, m, p * 2);
		// 如果左儿子代表的区间 [left,m] 与询问区间有交集,则递归查询左儿子
		if (right > m) sum += _getsum(left, right, m + 1, end, p * 2 + 1);
		// 如果右儿子代表的区间 [m+1,right] 与询问区间有交集,则递归查询右儿子
		return sum;
	}
public:
	SegTree(int n) {
		data = vector<int>(4 * n, 0);
		_size = n;
	}

	SegTree(vector<int>& origin) {
		int n = origin.size();
		_size = n;
		data = vector<int>(4 * n, 0);
		build(0, n - 1, 1, origin);
	}

	int getSum(int left, int right) {
		return _getsum(left, right, 0, _size - 1, 1);
	}
};