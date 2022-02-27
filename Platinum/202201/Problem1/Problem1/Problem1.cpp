#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <queue>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>

#ifdef INT_MAX
#undef INT_MAX
#endif

constexpr int INT_MAX = 2147483647;

using namespace std;

pair<int, int> merge_pair(pair<int, int> p1, pair<int, int> p2) {
	if ((p1.first == 0 && p1.second == 0) || (p2.first == 0 && p2.second == 0)) return { p1.first + p2.first, p1.second + p2.second };
	else return { min(p1.first, p2.first), max(p1.second, p2.second) };
}

class SegTree {
public:
	SegTree(int N) {
		vals.resize(N << 2, { 0, 0 });
		this->N = N;
	}

	void update(int query, int val) {
		update(query, val, 0, N - 1, 1);
	}

	pair<int, int> query(int d_left, int d_right) {
		return query(d_left, d_right, 0, N - 1, 1);
	}

private:
	void update(int query, int val, int left, int right, int ind) {
		if (left == right) {
			vals[ind] = { val, val };
			return;
		}

		int mid = (left + right) >> 1;
		if (query <= mid) update(query, val, left, mid, ind << 1);
		else update(query, val, mid + 1, right, (ind << 1) + 1);

		vals[ind] = merge_pair(vals[ind << 1], vals[(ind << 1) + 1]);
	}

	pair<int, int> query(int d_left, int d_right, int left, int right, int ind) {
		if (d_left == left && d_right == right) return vals[ind];

		int mid = (left + right) >> 1;
		pair<int, int> ans = { 0, 0 };
		if (d_left <= mid) ans = merge_pair(ans, query(d_left, min(d_right, mid), left, mid, ind << 1));
		if (d_right > mid) ans = merge_pair(ans, query(max(d_left, mid + 1), d_right, mid + 1, right, (ind << 1) + 1));
		return ans;
	}
	int N;
	vector<pair<int, int>> vals;
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	int N, K;
	cin >> N >> K;

	vector<int> hay(N);
	SegTree segtree(N);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q; // Number then index
	for (int i = 0; i < N; i++) {
		cin >> hay[i];

		segtree.update(i, hay[i]);

		pair<int, int> range = segtree.query(0, i);
		if (range.first >= hay[i] - K && range.second <= hay[i] + K) {
			Q.push({ hay[i], i });
			hay[i] = 0;
		}
	}

	vector<int> answer(N);
	for (int i = 0; i < N; i++) {
		auto temp = Q.top();
		int hay_size = temp.first;
		int ind = temp.second;
		Q.pop();

		answer[i] = hay_size;
		segtree.update(ind, 0);

		for (int j = ind + 1; j < N; j++) {
			if (hay[j] > 0) {
				pair<int, int> range = segtree.query(0, j - 1);
				if (range.first >= hay[i] - K && range.second <= hay[i] + K) {
					Q.push({ hay[j], j });
					hay[j] = 0;
				}
			}
		}
	}

	for (const auto num : answer) {
		cout << num << endl;
	}

	return 0;
}
