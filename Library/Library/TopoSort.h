#pragma once

#include <vector>
#include <queue>

using namespace std;

// Regular topological sort
vector<int> topoSort(int N, vector<vector<int>>& outEdges, vector<int>& numInEdges) {
	queue<int> Q;

	for (int i = 0; i < N; i++) {
		if (numInEdges[i] == 0) {
			Q.push(i);
		}
	}

	vector<int> ans;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();

		ans.push_back(u);
		for (const auto& v : outEdges[u]) {
			if (--numInEdges[v] == 0) {
				Q.push(v);
			}
		}
	}

	return ans;
}

// Topological sort with lexicographical order
vector<int> topoSortByLexOrder(int N, vector<vector<int>>& outEdges, vector<int>& numInEdges) {
	priority_queue<int, vector<int>, greater<int>> Q;

	for (int i = 0; i < N; i++) {
		if (numInEdges[i] == 0) {
			Q.push(i);
		}
	}

	vector<int> ans;
	while (!Q.empty()) {
		int u = Q.top();
		Q.pop();

		ans.push_back(u);
		for (const auto& v : outEdges[u]) {
			if (--numInEdges[v] == 0) {
				Q.push(v);
			}
		}
	}

	return ans;
}

