#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

constexpr long long MOD = 1000000007;

long long dfs(const vector<vector<int>>& edges, vector<int>& colors, int u, int parent, vector<vector<int>>& DP) {
	if (parent >= 0 && colors[u] == colors[parent]) return 0;

	if (parent >= 0 && DP[u][colors[parent]] >= 0) return DP[u][colors[parent]];

	long long total_ans = 0;
	int orig_c = colors[u];
	for (int c = 0; c < 3; c++) {
		// If a color is already assigned, use it.
		if (colors[u] >= 0 && colors[u] != c) continue;

		// Don't assing the same color as the parent.
		if (parent >= 0 && c == colors[parent]) continue;

		long long ans = 1;
		colors[u] = c;
		for (const auto& v : edges[u]) {
			if (v == parent) continue;

			ans = ans * dfs(edges, colors, v, u, DP) % MOD;
		}
		colors[u] = orig_c;

		total_ans = (total_ans + ans) % MOD;
	}

	if (parent >= 0) DP[u][colors[parent]] = total_ans;
	return total_ans;
}

int main() {
	ifstream in("barnpainting.in");
	int N, K;
	in >> N >> K;

	vector<vector<int>> edges(N);
	for (int i = 0; i < N - 1; i++) {
		int x, y;
		in >> x >> y;
		edges[x - 1].push_back(y - 1);
		edges[y - 1].push_back(x - 1);
	}

	vector<int> colors(N, -1);
	for (int i = 0; i < K; i++) {
		int b, c;
		in >> b >> c;
		colors[b - 1] = c - 1;
	}

	ofstream out("barnpainting.out");
	vector<vector<int>> DP(N, vector<int>(3, -1));
	out << dfs(edges, colors, 0, -1, DP) << endl;

	return 0;
}