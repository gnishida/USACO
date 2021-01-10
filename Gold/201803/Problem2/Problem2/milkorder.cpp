#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <queue>

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

vector<int> topoSort(int N, vector<vector<int>>& outEdges, vector<int>& numInEdges) {
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

int main() {
	ifstream in("milkorder.in");
	int N, M;
	in >> N >> M;

	ofstream out("milkorder.out");
	vector<vector<int>> outEdges(N);
	vector<int> numInEdges(N, 0);
	unordered_set<int> path;
	for (int i = 0; i < M; i++) {
		int num;
		in >> num;

		vector<int> A(num);
		for (int j = 0; j < num; j++) {
			in >> A[j];
			A[j]--;
		}

		bool cycled = false;
		int index = -1;
		for (int j = 1; j < num; j++) {
			outEdges[A[j - 1]].push_back(A[j]);
			numInEdges[A[j]]++;

			if (hasCycle(outEdges, A[j - 1], path)) {
				cycled = true;
				index = j;
				break;
			}
		}

		if (cycled) {
			for (int j = 1; j <= index; j++) {
				outEdges[A[j - 1]].pop_back();
				numInEdges[A[j]]--;
			}
			break;
		}
	}

	auto ans = topoSort(N, outEdges, numInEdges);
	for (int k = 0; k < ans.size(); k++) {
		if (k > 0) out << " ";
		out << ans[k] + 1;
	}

	return 0;
}