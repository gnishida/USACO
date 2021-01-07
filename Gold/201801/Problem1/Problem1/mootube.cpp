#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int getRoot(vector<int>& parents, int u) {
	if (parents[u] == -1) return u;

	int root = getRoot(parents, parents[u]);
	parents[u] = root;
	return root;
}

void merge(vector<int>& parents, vector<int>& sizes, int u, int v) {
	int root_u = getRoot(parents, u);
	int root_v = getRoot(parents, v);

	parents[root_v] = root_u;
	sizes[root_u] += sizes[root_v];
	sizes[root_v] = 0;
}

int main() {
	ifstream in("mootube.in");
	int N, Q;
	in >> N >> Q;

	map<int, vector<pair<int, int>>> edges;
	for (int i = 0; i < N - 1; i++) {
		int p, q, r;
		in >> p >> q >> r;
		edges[r].push_back({p - 1, q - 1});
	}

	map<int, vector<pair<int, int>>> queries;
	for (int i = 0; i < Q; i++) {
		int k, v;
		in >> k >> v;
		queries[k].push_back({ v - 1, i });
	}


	auto query_it = queries.rbegin();

	vector<int> ans(Q);
	vector<int> parents(N, -1);
	vector<int> sizes(N, 1);
	for (auto it = edges.rbegin(); it != edges.rend(); it++) {
		const auto& r = it->first;

		while (query_it != queries.rend() && query_it->first > r) {
			for (const auto& query : query_it->second) {
				const auto& u = query.first;
				const auto& query_index = query.second;
				ans[query_index] = sizes[getRoot(parents, u)] - 1;
			}

			query_it++;
		}

		for (const auto& p : it->second) {
			const auto& u = p.first;
			const auto& v = p.second;

			// merge u and v
			merge(parents, sizes, u, v);
		}
	}

	while (query_it != queries.rend()) {
		for (const auto& query : query_it->second) {
			const auto& u = query.first;
			const auto& query_index = query.second;
			ans[query_index] = sizes[getRoot(parents, u)] - 1;
		}

		query_it++;
	}

	ofstream out("mootube.out");
	for (const auto& a : ans) {
		out << a << endl;
	}

	return 0;
}