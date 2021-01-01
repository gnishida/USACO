#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

inline int dist(int u, int v) {
	return (2019201913LL * (min(u, v) + 1) + 2019201949LL * (max(u, v) + 1)) % 2019201997;
}

int main() {
	ifstream in("walk.in");
	int N, K;
	in >> N >> K;

	// True if the node is in the MST
	vector<bool> mst(N, false);

	// Node values for Prim's algorithm
	vector<int> dp(N, numeric_limits<int>::max());
	dp[0] = 0;

	// Perform Prim's algorithm
	for (int i = 0; i < N; i++) {
		// Find the smallest node that is not in the MST
		int minVal = numeric_limits<int>::max();
		int u = 0;
		for (int j = 1; j < N; j++) {
			if (mst[j]) continue;
			if (dp[j] < minVal) {
				minVal = dp[j];
				u = j;
			}
		}

		// Add the node to the MST
		mst[u] = true;

		// Update the values of the adjacent nodes
		for (int v = 0; v < N; v++) {
			if (v == u) continue;
			if (mst[v]) continue;

			dp[v] = min(dp[v], dist(u, v));
		}
	}

	ofstream out("walk.out");

	// (K-1)-th longest edge is the answer!
	sort(dp.begin(), dp.end());
	out << dp[N - K + 1] << endl;

	return 0;
}