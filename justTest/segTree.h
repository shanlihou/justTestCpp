#pragma once
#include <vector>
using namespace std;

class SegTree {
#define LAZY_DEF vector<int> lazy;
#define LAZY_INIT lazy = lazy = vector<int>(4 * n, 0)
#define LAZY_UPDATE lazy[p] += c;
#define LAZY_DOWN_DATA(data_1, data_2, lazy_p, dur_1, dur_2) \
    data_1 = data_1 * lazy_p * dur_1;\
    data_2 = data_2 * lazy_p * dur_2;

#define LAZY_DOWN_LAZY(lazy_1, lazy_2, lazy_p) \
    lazy_1 += lazy_p;\
    lazy_2 += lazy_p;\
    lazy_p = 0;

    // not need modify ----------------------------------------------------------------
#define LAZY_DOWN if (lazy[p]){\
    LAZY_DOWN_DATA(data[p * 2], data[p * 2 + 1], lazy[p], (mid - start + 1), (end - mid))\
    LAZY_DOWN_LAZY(lazy[p * 2], lazy[p * 2 + 1], lazy[p])\
}

#define LAZY_DOWN_GET if (lazy[p] && start != end){\
    LAZY_DOWN_DATA(data[p * 2], data[p * 2 + 1], lazy[p], (mid - start + 1), (end - mid))\
    LAZY_DOWN_LAZY(lazy[p * 2], lazy[p * 2 + 1], lazy[p])\
}


private:
    vector<int> data;
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
        // [left,right] Ϊ��ѯ����,[start,end] Ϊ��ǰ�ڵ����������,pΪ��ǰ�ڵ�ı��
        if (left <= start && end <= right)
            return data[p];
        // ��ǰ����Ϊѯ��������Ӽ�ʱֱ�ӷ��ص�ǰ����ĺ�
        int mid = (start + end) / 2;
        LAZY_DOWN
            int sum = 0;
        if (left <= mid) sum = _getsum(left, right, start, mid, p * 2);
        if (right > mid) sum += _getsum(left, right, mid + 1, end, p * 2 + 1);
        return sum;
    }

    void _update(int left, int right, int c, int start, int end, int p) {
        // [left,right] Ϊ�޸�����,c Ϊ���޸ĵ�Ԫ�صı仯��,[start,end] Ϊ��ǰ�ڵ����������,p
        // Ϊ��ǰ�ڵ�ı��
        if (left <= start && end <= right) {
            data[p] = data[p] + (end - start + 1) * c;
            LAZY_UPDATE;
            return;
        }  // ��ǰ����Ϊ�޸�������Ӽ�ʱֱ���޸ĵ�ǰ�ڵ��ֵ,Ȼ�����,�����޸�
        int mid = (start + end) / 2;
        LAZY_DOWN_GET

        if (left <= mid) _update(left, right, c, start, mid, p * 2);
        if (right > mid) _update(left, right, c, mid + 1, end, p * 2 + 1);
        data[p] = data[p * 2] + data[p * 2 + 1];
    }
public:
    SegTree(int n) {
        data = vector<int>(4 * n, 0);
        LAZY_INIT;
        _size = n;
    }

    SegTree(vector<int>& origin) {
        int n = origin.size();
        _size = n;
        data = vector<int>(4 * n, 0);
        LAZY_INIT;
        build(0, n - 1, 1, origin);
    }

    int getSum(int left, int right) {
        return _getsum(left, right, 0, _size - 1, 1);
    }

    void update(int left, int right, int c) {
        _update(left, right, c, 0, _size - 1, 1);
    }
};

#if 0
class SegTree {
private:
	vector<int> data;
	vector<int> lazy;
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
		// [left,right] Ϊ��ѯ����,[start,end] Ϊ��ǰ�ڵ����������,pΪ��ǰ�ڵ�ı��
		if (left <= start && end <= right) return data[p];
		// ��ǰ����Ϊѯ��������Ӽ�ʱֱ�ӷ��ص�ǰ����ĺ�
		int mid = (start + end) / 2;
		if (lazy[p]) {
			// �����ǰ�ڵ������Ƿǿ�,����µ�ǰ�ڵ������ӽڵ��ֵ�������ֵ
			data[p * 2] += lazy[p] * (mid - start + 1);
			data[p * 2 + 1] += lazy[p] * (end - mid);
			lazy[p * 2] += lazy[p];
			lazy[p * 2 + 1] += lazy[p];  // ������´����ӽڵ�
			lazy[p] = 0;                                    // ��յ�ǰ�ڵ�ı��
		}
		int sum = 0;
		if (left <= mid) sum = _getsum(left, right, start, mid, p * 2);
		if (right > mid) sum += _getsum(left, right, mid + 1, end, p * 2 + 1);
		return sum;
	}

	void update(int left, int right, int c, int start, int end, int p) {
		// [left,right] Ϊ�޸�����,c Ϊ���޸ĵ�Ԫ�صı仯��,[start,end] Ϊ��ǰ�ڵ����������,p
		// Ϊ��ǰ�ڵ�ı��
		if (left <= start && end <= right) {
			data[p] += (end - start + 1) * c, lazy[p] += c;
			return;
		}  // ��ǰ����Ϊ�޸�������Ӽ�ʱֱ���޸ĵ�ǰ�ڵ��ֵ,Ȼ�����,�����޸�
		int mid = (start + end) / 2;
		if (lazy[p] && start != end) {
			// �����ǰ�ڵ������Ƿǿ�,����µ�ǰ�ڵ������ӽڵ��ֵ�������ֵ
			data[p * 2] += lazy[p] * (mid - start + 1), data[p * 2 + 1] += lazy[p] * (end - mid);
			lazy[p * 2] += lazy[p], lazy[p * 2 + 1] += lazy[p];  // ������´����ӽڵ�
			lazy[p] = 0;                                // ��յ�ǰ�ڵ�ı��
		}
		if (left <= mid) update(left, right, c, start, mid, p * 2);
		if (right > mid) update(left, right, c, mid + 1, end, p * 2 + 1);
		data[p] = data[p * 2] + data[p * 2 + 1];
	}
public:
	SegTree(int n) {
		data = vector<int>(4 * n, 0);
		lazy = vector<int>(4 * n, 0);
		_size = n;
	}

	SegTree(vector<int>& origin) {
		int n = origin.size();
		_size = n;
		data = vector<int>(4 * n, 0);
		lazy = vector<int>(4 * n, 0);
		build(0, n - 1, 1, origin);
	}

	int getSum(int left, int right) {
		return _getsum(left, right, 0, _size - 1, 1);
	}
};
#endif