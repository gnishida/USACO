#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct TreeNode {
	int parent;
	int size;
	long long dist;
	vector<int> children;
};

int dfs(const vector<vector<pair<int, int>>>& edges, const vector<int>& cows, int u, int parent, vector<TreeNode>& nodes) {
	nodes[u].size = cows[u];
	for (const auto& v : nodes[u].children) {
		nodes[u].size += dfs(edges, cows, v, u, nodes);
	}
	return nodes[u].size;
}

int main() {
	ifstream in("shortcut.in");
	int N, M, T;
	in >> N >> M >> T;

	vector<int> cows(N);
	for (int i = 0; i < N; i++) {
		in >> cows[i];
	}

	vector<vector<pair<int, int>>> edges(N);
	for (int i = 0; i < M; i++) {
		int a, b, t;
		in >> a >> b >> t;
		edges[a - 1].push_back({ b - 1, t });
		edges[b - 1].push_back({ a - 1, t });
	}

	// Initialize tree nodes
	vector<TreeNode> nodes(N);
	for (int i = 0; i < N; i++) {
		nodes[i].dist = numeric_limits<int>::max();
	}

	// Dijkstra
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> Q;
	Q.push({ 0, 0 });
	nodes[0].dist = 0;
	while (!Q.empty()) {
		long long dist = Q.top().first;
		int u = Q.top().second;
		Q.pop();

		if (dist > nodes[u].dist) continue;

		for (const auto& p : edges[u]) {
			int v = p.first;
			long long d = p.second;
			if (v == nodes[u].parent) continue;

			long long new_dist = nodes[u].dist + d;
			if (new_dist < nodes[v].dist || (new_dist == nodes[v].dist && u < nodes[v].parent)) {
				nodes[v].dist = new_dist;
				nodes[v].parent = u;
				Q.push({ new_dist, v });
			}
		}
	}

	// Determine the children for the nodes
	for (int i = 1; i < N; i++) {
		nodes[nodes[i].parent].children.push_back(i);
	}

	// DFS to calculate size of subtrees
	dfs(edges, cows, 0, -1, nodes);

	// Find the best node to connect the short cut
	long long ans = 0;
	for (int i = 1; i < N; i++) {
		ans = max(ans, (nodes[i].dist - T) * nodes[i].size);
	}

	ofstream out("shortcut.out");
	out << ans << endl;

	return 0;
}