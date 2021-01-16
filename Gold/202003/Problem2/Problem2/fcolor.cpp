#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int getRoot(vector<int>& parents, int u) {
	if (parents[u] == -1) return u;

	int root = getRoot(parents, parents[u]);
	parents[u] = root;
	return root;
}

void unionSet(vector<vector<int>>& edges, vector<int>& parents, int u, int v) {
	int root_u = getRoot(parents, u);
	int root_v = getRoot(parents, v);

	if (root_v == root_u) return;

	parents[root_v] = root_u;

	edges[root_u].insert(edges[root_u].end(), edges[root_v].begin(), edges[root_v].end());
	edges[root_v].clear();
}

int main() {
	ifstream in("fcolor.in");
	int N, M;
	in >> N >> M;

	vector<vector<int>> edges(N);
	for (int i = 0; i < M; i++) {
		int a, b;
		in >> a >> b;
		edges[a - 1].push_back(b - 1);
	}

	// Initialize
	vector<int> parents(N, -1);
	queue<int> Q;
	for (int u = 0; u < N; u++) {
		if (edges[u].size() >= 2) {
			Q.push(u);
		}
	}

	// DSU
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();

		if (edges[u].size() <= 1) continue;

		// Merge children
		int first_child = edges[u][0];
		int first_root = getRoot(parents, first_child);
		for (const auto& v : edges[u]) {
			unionSet(edges, parents, first_child, v);
		}

		// Remove edges for the deleted children
		edges[u].clear();
		edges[u].push_back(first_root);

		if (edges[first_root].size() >= 2) {
			Q.push(first_root);
		}
	}

	ofstream out("fcolor.out");
	vector<int> colors(N, -1);
	int color = 1;
	for (int i = 0; i < N; i++) {
		int root = getRoot(parents, i);
		if (colors[root] == -1) {
			colors[root] = color++;
		}

		out << colors[root] << endl;
	}

	return 0;
}