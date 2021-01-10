#pragma once

#include <vector>
#include <queue>
#include <unordered_set>


using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////
// Array related algorithm

// Binary search
class BinarySearch {
public:
	BinarySearch(const vector<int>& A) : N(A.size()), data(A) {}

	int lowerBound(int query) {
		return lowerBound(0, N - 1, query);
	}

private:
	int lowerBound(int left, int right, int query) {
		if (left >= right) {
			if (query <= data[left]) return left;
			else return left + 1;
		}

		int m = (left + right) / 2;
		if (query <= data[m]) {
			return lowerBound(left, m, query);
		} else {
			return lowerBound(m + 1, right, query);
		}
	}

private:
	int N;
	const vector<int>& data;
};


// Merge sort
vector<int> mergeSort(vector<int>& A, int left, int right) {
	if (left == right) return { A[left] };

	int m = (left + right) / 2;
	auto L = mergeSort(A, left, m);
	auto R = mergeSort(A, m + 1, right);

	vector<int> ret(right - left + 1);
	int index = 0;
	int indexL = 0;
	int indexR = 0;

	while (indexL < L.size() || indexR < R.size()) {
		if (indexL < L.size() && (indexR >= R.size() || L[indexL] <= R[indexR])) {
			ret[index++] = L[indexL++];
		} else {
			ret[index++] = R[indexR++];
		}
	}

	return ret;
}


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

// Dijkstra for shortest path
// edgse contain edge <v, weight>
vector<int> dijkstra(int N, vector<vector<pair<int, int>>>& edges, int start) {
	// Shortest distance from the start node
	vector<int> DP(N, numeric_limits<int>::max());
	DP[start] = 0;

	int done = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	Q.push({ 0, start });

	while (!Q.empty()) {
		int d = Q.top().first;
		int u = Q.top().second;
		Q.pop();
		if (d > DP[u]) continue;

		done++;

		for (const auto& p : edges[u]) {
			const auto& v = p.first;
			const auto& w = p.second;
			int new_d = d + w;
			if (new_d < DP[v]) {
				DP[v] = new_d;
				Q.push({ new_d, v });
			}
		}
	}

	// done has to be N!
	if (done < N) throw "There are some unreachable nodes";

	return DP;
}


// Floyd-Warshall for shotest path from all nodes
// edgse contain edge <v, weight>
vector<vector<int>> floyd_warshall(int N, vector<vector<pair<int, int>>>& edges) {
	vector<vector<int>> DP(N, vector<int>(N, numeric_limits<int>::max()));

	// Initialize the distance between nodes
	for (int u = 0; u < N; u++) {
		for (const auto& p : edges[u]) {
			const auto& v = p.first;
			const auto& w = p.second;
			DP[u][v] = w;
		}
	}
	for (int u = 0; u < N; u++) {
		DP[u][u] = 0;
	}

	for (int k = 0; k < N; k++) {
		for (int u = 0; u < N; u++) {
			for (int v = 0; v < N; v++) {
				DP[u][v] = min(DP[u][v], DP[u][k] + DP[k][v]);
			}
		}
	}

	return DP;
}


// Kruskal for MST
// Use Kruskal for sparse graph!
int kruskal_getRoot(vector<int>& parents, int u) {
	if (parents[u] == -1) return u;

	int root = kruskal_getRoot(parents, parents[u]);
	parents[u] = root;
	return root;
}

void kruskal_merge(vector<int>& parents, int u, int v) {
	int root_u = kruskal_getRoot(parents, u);
	int root_v = kruskal_getRoot(parents, v);

	parents[root_v] = root_u;
}

// edges contain edge <weight, <u, v>>
vector<pair<int, int>> kruskal(int N, vector<pair<int, pair<int, int>>>& edges, int exclude_edge) {
	vector<int> parents(N, -1);
	int numGroups = N;

	vector<pair<int, int>> mstEdges;

	sort(edges.begin(), edges.end());

	for (const auto& edge : edges) {
		const auto& w = edge.first;
		const auto& u = edge.second.first;
		const auto& v = edge.second.second;

		int root_u = kruskal_getRoot(parents, u);
		int root_v = kruskal_getRoot(parents, v);
		if (root_u == root_v) continue;

		// Use this edge and merge u and v
		mstEdges.push_back({ u, v });
		kruskal_merge(parents, u, v);
		numGroups--;
	}

	// numGroups must be 1!
	if (numGroups > 1) throw "There are some disconnected nodes";

	return mstEdges;
}


/// Prim for MST
/// Use Prim for dense graph!
///
/// \param	N number of nodes
/// \edges  edges that contain <v, weight>
/// \return sum of edge lengths in MST
int prim(int N, vector<vector<int>>& edges) {
	vector<int> DP(N, numeric_limits<int>::max());
	DP[0] = 0;
	vector<int> parents(N, -1);
	vector<bool> done(N, false);
	int ans = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	Q.push({ 0, 0 });

	while (!Q.empty()) {
		int d = Q.top().first;
		int u = Q.top().second;
		Q.pop();

		if (d > DP[u]) continue;

		done[u] = true;
		if (parents[u] >= 0) {
			ans += edges[parents[u]][u];
		}

		for (int v = 0; v < N; v++) {
			if (v == u || done[v]) continue;
			const auto& w = edges[u][v];

			if (w < DP[v]) {
				DP[v] = w;
				parents[v] = u;
				Q.push({ w, v });
			}
		}
	}

	return ans;
}


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

