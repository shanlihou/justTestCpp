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
		// [left,right] Ϊ��ѯ����,[start,end] Ϊ��ǰ�ڵ����������,p Ϊ��ǰ�ڵ�ı��
		if (left <= start && end <= right)
			return data[p];  // ��ǰ����Ϊѯ��������Ӽ�ʱֱ�ӷ��ص�ǰ����ĺ�
		int m = (start + end) / 2, sum = 0;
		if (left <= m) sum += _getsum(left, right, start, m, p * 2);
		// �������Ӵ�������� [left,m] ��ѯ�������н���,��ݹ��ѯ�����
		if (right > m) sum += _getsum(left, right, m + 1, end, p * 2 + 1);
		// ����Ҷ��Ӵ�������� [m+1,right] ��ѯ�������н���,��ݹ��ѯ�Ҷ���
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