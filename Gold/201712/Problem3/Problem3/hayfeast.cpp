#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class SegTree {
public:
	SegTree(int n) {
		N = n;
		data.resize(n * 4, 0);
	}

	void update(int index, int left, int right, int query_index, int val) {
		data[index] = max(data[index], val);
		if (left == right) return;

		int m = (left + right) / 2;
		if (query_index <= m) {
			update(index * 2, left, m, query_index, val);
		} else {
			update(index * 2 + 1, m + 1, right, query_index, val);
		}
	}

	int query(int index, int left, int right, int query_left, int query_right) {
		if (query_left == left && query_right == right) return data[index];
		
		int ans = 0;

		int m = (left + right) / 2;
		if (query_left <= m) {
			ans = max(ans, query(index * 2, left, m, query_left, min(m, query_right)));
		}
		if (query_right > m) {
			ans = max(ans, query(index * 2 + 1, m + 1, right, max(m + 1, query_left), query_right));
		}

		return ans;
	}

private:
	int N;
	vector<int> data;
};

int main() {
	ifstream in("hayfeast.in");
	int N;
	long long M;
	in >> N >> M;

	vector<int> F(N);
	SegTree S(N);

	for (int i = 0; i < N; i++) {
		int f, s;
		in >> F[i] >> s;
		S.update(1, 0, N - 1, i, s);

	}
	
	int left = 0;
	int right = -1;
	long long totalF = 0;
	int ans = numeric_limits<int>::max();
	while (right < N) {
		if (totalF < M) {
			if (++right >= N) break;;
			totalF += F[right];
		} else {
			ans = min(ans, S.query(1, 0, N - 1, left, right));
			totalF -= F[left++];
		}
	}

	ofstream out("hayfeast.out");
	out << ans << endl;

	return 0;
}