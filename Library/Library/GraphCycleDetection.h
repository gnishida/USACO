#pragma once

#include <vector>
#include <unordered_set>

using namespace std;


bool hasCycle(const vector<vector<int>>& edges, int u, unordered_set<int>& path) {
	if (path.find(u) != path.end()) return true;

	path.insert(u);
	for (const auto& v : edges[u]) {
		if (hasCycle(edges, v, path)) return true;
	}
	path.erase(u);

	return false;
}
