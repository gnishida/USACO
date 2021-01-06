#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int lowerBound(const vector<pair<long long, int>>& nums, int left, int right, long long query) {
	if (left == right) {
		if (query <= nums[left].first) return left;
		else return left + 1;
	}

	int m = (left + right) / 2;
	if (query <= nums[m].first) {
		return lowerBound(nums, left, m, query);
	} else {
		return lowerBound(nums, m + 1, right, query);
	}
}

int solve(const vector<vector<int>>& adj, int u, vector<int>& visited) {
	if (adj[u].size() == 0) return 1;

	visited[u] = true;

	int ans = numeric_limits<int>::max();
	for (const auto& v : adj[u]) {
		if (visited[v]) continue;
		int ret = solve(adj, v, visited);
		if (ret >= 0) {
			ans = min(ans, ret + 1);
		}
	}

	visited[u] = false;

	if (ans < numeric_limits<int>::max()) {
		return ans;
	} else {
		return -1;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	ifstream in("piepie.in");
	int N, D;
	in >> N >> D;

	vector<pair<long long, long long>> pies(N * 2);
	vector<pair<long long, int>> ordered1(N);
	vector<pair<long long, int>> ordered2(N);
	for (int i = 0; i < N * 2; i++) {
		in >> pies[i].first >> pies[i].second;
		if (i < N) {
			ordered1[i] = { pies[i].first, i };
		} else {
			ordered2[i - N] = { pies[i].second, i };
		}
	}

	sort(ordered1.begin(), ordered1.end());
	sort(ordered2.begin(), ordered2.end());

	// Construct edges
	vector<vector<int>> inEdges(N * 2);
	for (int i = 0; i < N; i++) {
		int index = lowerBound(ordered2, 0, N - 1, pies[i].second);
		for (int j = index; j < N; j++) {
			if (ordered2[j].first > pies[i].second + D) break;
			inEdges[ordered2[j].second].push_back(i);
		}
	}
	for (int i = N; i < N * 2; i++) {
		int index = lowerBound(ordered1, 0, N - 1, pies[i].first);
		for (int j = index; j < N; j++) {
			if (ordered1[j].first > pies[i].first + D) break;
			inEdges[ordered1[j].second].push_back(i);
		}
	}

	// Dijkstra
	vector<int> DP(N * 2, numeric_limits<int>::max());
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	for (int i = 0; i < N * 2; i++) {
		if (i < N) {
			if (pies[i].second == 0) {
				Q.push({ i, 1 });
				DP[i] = 1;
			}
		} else {
			if (pies[i].first == 0) {
				Q.push({ i, 1 });
				DP[i] = 1;
			}
		}
	}
	while (!Q.empty()) {
		int u = Q.top().first;
		int d = Q.top().second;
		Q.pop();

		if (d > DP[u]) continue;

		for (const auto& v : inEdges[u]) {
			int new_dist = DP[u] + 1;
			if (new_dist < DP[v]) {
				DP[v] = new_dist;
				Q.push({ v, new_dist });
			}
		}
	}

	ofstream out("piepie.out");
	for (int i = 0; i < N; i++) {
		if (DP[i] < numeric_limits<int>::max()) {
			out << DP[i] << endl;
		} else {
			out << -1 << endl;
		}
	}

	return 0;
}
