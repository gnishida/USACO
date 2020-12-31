#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;


class SegmentTree {
public:
	SegmentTree(int n) {
		N = n;
		data.resize(n * 4, 0);
	}

	void update(int index, int val) {
		update(1, 0, N - 1, index, val);
	}

	void update(int index, int left, int right, int query_index, int val) {
		data[index] += val;

		if (left == right) return;

		int m = (left + right) / 2;
		if (query_index <= m) {
			update(index * 2, left, m, query_index, val);
		} else {
			update(index * 2 + 1, m + 1, right, query_index, val);
		}
	}

	int query(int left, int right) {
		return query(1, 0, N - 1, left, right);
	}

	int query(int index, int left, int right, int query_left, int query_right) {
		if (left == query_left && right == query_right) {
			return data[index];
		}
				
		int ret = 0;
		int m = (left + right) / 2;
		if (query_left <= m) {
			ret += query(index * 2, left, m, query_left, min(m, query_right));
		}
		if (query_right > m) {
			ret += query(index * 2 + 1, m + 1, right, max(query_left, m + 1), query_right);
		}

		return ret;
	}

private:
	int N;
	vector<int> data;
};

int main() {
	ifstream in("sleepy.in");
	int N;
	in >> N;

	vector<int> A(N);
	for (int i = 0; i < N; i++) {
		in >> A[i];
		A[i]--;
	}

	SegmentTree segTree(N);

	// Find sorted sequence from the last
	int cnt = 1;
	int prev = A.back();
	segTree.update(A.back(), 1);
	for (int i = N - 2; i >= 0; i--) {
		if (A[i] > prev) {
			break;
		}
		segTree.update(A[i], 1);
		prev = A[i];
		cnt++;
	}

	ofstream out("sleepy.out");
	out << N - cnt << endl;
	for (int i = 0; i < N - cnt; i++) {
		if (i > 0) out << " ";
		out << N - cnt - i + segTree.query(0, A[i]) - 1;
		segTree.update(A[i], 1);
	}
	out << endl;

	return 0;
}