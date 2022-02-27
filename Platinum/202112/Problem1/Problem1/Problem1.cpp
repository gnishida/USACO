#include <vector>
#include <queue>
#include <unordered_set>
#include <set>
#include <stack>
#include <iostream>

#ifndef MAX_VAL
#define MAX_VAL 2147483647
#endif

using namespace std;

vector<int> prices;
vector<int> sources;
vector<pair<int, int>> dests;


// Segment tree for range sum
class SegmentTree {
public:
	SegmentTree(int n) {
		N = n;
		data.resize(n * 4);
	}

	// Add the value to the index-th element
	void add(int query_index, int val) {
		add(1, 0, N - 1, query_index, query_index, val);
	}

	void add(int query_left, int query_right, int val) {
		add(1, 0, N - 1, query_left, query_right, val);
	}

	void add(int index, int left, int right, int query_left, int query_right, int val) {
		if (left == right || (left == query_left && right == query_right)) {
			data[index].push_back(val);
			return;
		}

		int m = (left + right) / 2;
		if (query_left <= m) {
			add(index * 2, left, m, query_left, min(m, query_right), val);
		}
		if (query_right > m) {
			add(index * 2 + 1, m + 1, right, max(m + 1, query_left), query_right, val);
		}
	}

	// Get list of edge indices
	void query(int query_index, vector<int>& results) {
		query(1, 0, N - 1, query_index, query_index, results);
	}

	void query(int index, int left, int right, int query_left, int query_right, vector<int>& results) {
		results.insert(results.end(), data[index].begin(), data[index].end());

		if (left == right) {
			return;
		}

		int m = (left + right) / 2;
		if (query_left <= m) {
			query(index * 2, left, m, query_left, min(m, query_right), results);
		}
		if (query_right > m) {
			query(index * 2 + 1, m + 1, right, max(m + 1, query_left), query_right, results);
		}
	}

private:
	int N;
	vector<vector<int>> data;
};


int main() {
	int N, K;
	cin >> N >> K;
	
	prices.resize(K);
	sources.resize(K);
	dests.resize(K);

	SegmentTree segTree(N);

	for (int i = 0; i < K; i++) {
		int c, p, a, b;
		cin >> c >> p >> a >> b;
		c--;
		a--;
		b--;
		sources[i] = c;
		prices[i] = p;
		dests[i].first = a;
		dests[i].second = b;
		segTree.add(a, b, i);
	}

	vector<vector<long long>> DP(N, vector<long long>(3, MAX_VAL));
	DP[0][0] = 0;
	DP[N - 1][1] = 0;
	vector<vector<long long>> DP_E(K, vector<long long>(3, MAX_VAL));

	queue<int> Q;
	Q.push(0);
	Q.push(N - 1);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();

		vector<int> edges;
		segTree.query(u, edges);
		for (const auto& e : edges) {
			// Update DP_E
			for (int i = 0; i < 3; i++) {
				DP_E[e][i] = min(DP_E[e][i], DP[u][i]);
			}
			if (dests[e].first == 0) {
				DP_E[e][0] = 0;
			}
			if (dests[e].second == N - 1) {
				DP_E[e][1] = 0;
			}

			const auto& v = sources[e];
			const auto& price = prices[e];

			// 0 reach cost
			if (DP_E[e][0] < MAX_VAL && DP_E[e][0] + price < DP[v][0]) {
				DP[v][0] = DP_E[e][0] + price;
				Q.push(v);
			}

			// N -1 reach cost
			if (DP_E[e][1] < MAX_VAL && DP_E[e][1] + price < DP[v][1]) {
				DP[v][1] = DP_E[e][1] + price;
				Q.push(v);
			}

			// Both 0/N -1 reach cost
			if (DP[v][0] < MAX_VAL && DP[v][1] < MAX_VAL) {
				DP[v][2] = min(DP[v][2], DP[v][0] + DP[v][1]);
			}
			if (DP_E[e][0] < MAX_VAL && DP_E[e][1] < MAX_VAL && DP_E[e][0] + DP_E[e][1] + price < DP[v][2]) {
				DP[v][2] = min(DP[v][2], DP_E[e][0] + DP_E[e][1] + price);
			}
			if (DP_E[e][2] < MAX_VAL) {
				DP[v][2] = min(DP[v][2], DP_E[e][2] + price);
			}
		}
	}

	for (int i = 0; i < N; i++) {
		if (DP[i][2] < MAX_VAL) {
			cout << DP[i][2] << endl;
		} else {
			cout << -1 << endl;
		}
	}

	return 0;
}
