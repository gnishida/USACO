#pragma once

#include <vector>
#include <queue>
#include <unordered_set>


using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tree related algorithm

// Binary indexed tree for numbers [0, ..., N - 1].
class BIT {
public:
	BIT(int N) {
		this->N = N;
		data.resize(N + 1, 0);
	}

	// Add val to the index-th element
	void add(int index, int val) {
		index++;
		while (index <= N) {
			data[index] += val;
			index += index & -index;
		}
	}

	// Get sum from 0 to index-th element
	int query(int index) {
		index++;
		int sum = 0;
		while (index > 0) {
			sum += data[index];
			index -= index & -index;
		}
		return sum;
	}

private:
	int N;
	vector<int> data;
};

// Segment tree
class SegmentTree {
public:
	SegmentTree(int n) {
		N = n;
		data.resize(n * 4, 0);
	}

	// Add the value to the index-th element
	void add(int query_index, int val) {
		add(1, 0, N - 1, query_index, val);
	}

	void add(int index, int left, int right, int query_index, int val) {
		data[index] += val;

		if (left == right) return;

		int m = (left + right) / 2;
		if (query_index <= m) {
			add(index * 2, left, m, query_index, val);
		} else {
			add(index * 2 + 1, m + 1, right, query_index, val);
		}
	}

	// Get sum of elements between query_left and query_right
	int query(int query_left, int query_right) {
		return query(1, 0, N - 1, query_left, query_right);
	}

	int query(int index, int left, int right, int query_left, int query_right) {
		if (left == query_left && right == query_right) return data[index];

		int ans = 0;

		int m = (left + right) / 2;
		if (query_left <= m) {
			ans += query(index * 2, left, m, query_left, min(m, query_right));
		}
		if (query_right > m) {
			ans += query(index * 2 + 1, m + 1, right, max(m + 1, query_left), query_right);
		}

		return ans;
	}

private:
	int N;
	vector<int> data;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////
// Graph related algorithm

// Perform topological sort and return the sorted nodes.
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

// Check if the graph has a cycle starting from a node u
// Note: This is not for checking a cycle for the entire graph.
bool hasCycle(const vector<vector<int>>& edges, int u, unordered_set<int>& path) {
	if (path.find(u) != path.end()) return true;

	path.insert(u);
	for (const auto& v : edges[u]) {
		if (hasCycle(edges, v, path)) return true;
	}
	path.erase(u);

	return false;
}

