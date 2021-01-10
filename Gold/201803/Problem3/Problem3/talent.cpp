#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

bool compare(const pair<int, int>& v1, const pair<int, int>& v2) {
	return double(v1.second) / v1.first > double(v2.second) / v2.first;
}

int main() {
	ifstream in("talent.in");
	int N, W;
	in >> N >> W;

	vector<pair<int, int>> A(N);
	for (int i = 0; i < N; i++) {
		in >> A[i].first >> A[i].second;
	}

	sort(A.begin(), A.end(), compare);

	double ans = 0;
	vector<unordered_map<int, int>> DP(N + 1);
	DP[0][0] = 0;
	for (int i = 0; i < N; i++) {
		unordered_set<int> newS;
		for (const auto& p : DP[i]) {
			const int& j = p.first;

			DP[i + 1][j] = max(DP[i + 1][j], DP[i][j]);

			const int& w = A[i].first;
			const int& t = A[i].second;
			
			const int new_t = DP[i][j] + t;
			const int new_j = j + w;
			const double new_ratio = double(new_t) / new_j;
			if (new_ratio < ans) continue;

			if (new_j >= W) {
				ans = max(ans, new_ratio);
			}

			DP[i + 1][new_j] = max(DP[i + 1][new_j], new_t);
		}
	}

	ofstream out("talent.out");
	out << int(ans * 1000) << endl;

	return 0;
}