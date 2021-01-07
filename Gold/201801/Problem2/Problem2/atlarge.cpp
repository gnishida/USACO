#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, int> dfs(const vector<vector<int>>& edges, int u, int parent, int depth) {
	int minHeight = numeric_limits<int>::max();
	int count = 0;

	for (const auto& v : edges[u]) {
		if (v == parent) continue;
		auto ret = dfs(edges, v, u, depth + 1);
		minHeight = min(minHeight, ret.first + 1);
		count += ret.second;
	}
	if (minHeight == numeric_limits<int>::max()) minHeight = 0;

	if (depth >= minHeight) {
		return { minHeight, 1 };
	} else {
		return { minHeight, count };
	}
}

int main() {
	ifstream in("atlarge.in");
	int N, K;
	in >> N >> K;

	vector<vector<int>> edges(N);
	for (int i = 0; i < N - 1; i++) {
		int a, b;
		in >> a >> b;
		edges[a - 1].push_back(b - 1);
		edges[b - 1].push_back(a - 1);
	}

	ofstream out("atlarge.out");
	out << dfs(edges, K - 1, -1, 0).second << endl;

	return 0;
}